/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:32:30 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/30 18:36:44 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	read_all_file(char *file_name, t_data *data)
{
	int		fd;
	char	buffer[1025];
	int		bytes_read;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_clean_exit(data, 1, "Cannot get fd");
	bytes_read = 1;
	data->buffer = NULL;
	while (bytes_read > 0)
	{
		ft_bzero(buffer, 1025);
		bytes_read = read(fd, buffer, 1024);
		data->buffer = ft_strjoinfree(data->buffer, buffer);
		if (bytes_read == -1 || data->buffer == NULL)
			ft_clean_exit(data, 1, "Fail in read or strjoin");
	}
}

static void	set_direction(char c, t_data *data)
{
	if (c == 'S')
	{
		data->direction.x = 0.0;
		data->direction.y = 1.0;
		data->cameraplane.x = -0.66;
		data->cameraplane.y = 0.0;
	}
	else if (c == 'E')
	{
		data->direction.x = 1.0;
		data->direction.y = 0.0;
		data->cameraplane.x = 0.0;
		data->cameraplane.y = 0.66;
	}
	else if (c == 'W')
	{
		data->direction.x = -1.0;
		data->direction.y = 0.0;
		data->cameraplane.x = 0.0;
		data->cameraplane.y = -0.66;
	}
}

int	get_player(char **map, int i, int j)
{
	t_data	*data;
	char	c;

	data = get_data();
	c = map[j][i];
	if (ft_strchr("NSWE", c))
	{
		data->player_pos.x = i + 0.5;
		data->player_pos.y = j + 0.5;
		map[j][i] = '0';
		set_direction(c, data);
		return (1);
	}
	return (0);
}

void	check_borders(t_data *data, char **map, int pcount)
{
	int	j;
	int	i;

	if (!is_all_space_n_ones(map[0]))
		ft_clean_exit(data, 1, "Missing outside wall (top)");
	j = 1;
	while (map[j])
	{
		if (vertical_walls(map[j]))
			ft_clean_exit(data, 1, "Missing outside wall (vertical)");
		i = 0;
		while (map[j][i])
		{
			if (!ft_strchr("01NSWE MD", map[j][i]))
				ft_clean_exit(data, 1, "Map char unvalid");
			pcount += get_player(map, i, j);
			leak_check(map, i, j);
			i++;
		}
		j++;
	}
	if (!is_all_space_n_ones(map[j - 1]))
		ft_clean_exit(data, 1, "Missing outside wall (bottom)");
	if (pcount != 1)
		ft_clean_exit(data, 1, "Incorrect number of player starting point");
}

void	check_map(t_data *data, char **map)
{
	int	pcount;

	pcount = 0;
	check_borders(data, map, pcount);
}

void	get_map(char *file_name)
{
	t_data	*data;

	init_data();
	data = get_data();
	read_all_file(file_name, data);
	if (data->buffer && *data->buffer)
		data->map = ft_split(data->buffer, '\n');
	if (!data->map)
	{
		perror("Error\n");
		free(data->buffer);
		exit(EXIT_FAILURE);
	}
	read_textures(&data->map);
	check_map(data, data->map);
	monster_init(data, 0, 0);
	doors_init(data, 0, 0);
}
