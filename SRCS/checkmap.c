/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:32:30 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/05 15:47:09 by manon            ###   ########.fr       */
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

void	check_borders(t_data *data, char **map, int pcount)
{
	int				j;
	int				i;

	if (!is_all_c(map[0], '1'))
		ft_clean_exit(data, 1, "Missing outside wall");
	j = 1;
	while (map[j])
	{
		ft_strlen(map[j]);
		if (map[j][0] != '1' || map[j][ft_strlen(map[j]) - 1] != '1')
			ft_clean_exit(data, 1, "Missing outside wall");
		i = 0;
		while (map[j][i])
		{
			if (!ft_strchr("01NSWE", map[j][i]))
				ft_clean_exit(data, 1, "Map char unvalid");
			if (ft_strchr("NSWE", map[j][i]))
				pcount++;
			i++;
		}
		j++;
	}
	if (!is_all_c(map[j - 1], '1'))
		ft_clean_exit(data, 1, "Missing outside wall");
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
	read_textures(&data->map);
	if (!data->map)
	{
		// perror("Error\n");
		// ft
		free(data->buffer);
		exit(EXIT_FAILURE);
	}
	check_map(data, data->map);
}
