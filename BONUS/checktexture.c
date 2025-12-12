/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:43:02 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/01 02:04:40 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

int	import_tex(int index, int which, char *line)
{
	int		count;
	t_data	*data;

	count = 0;
	data = get_data();
	while (line[index] && line[index] == ' ')
		index++;
	while (line[index + count] && line[index + count] != ' ')
		count ++;
	if (line[count + index])
	{
		ft_clean_exit(get_data(), 1, "Error\ntex format incorrect\n");
		return (1);
	}
	if (data->tex[which].path)
		free(data->tex[which].path);
	data->tex[which].path = ft_substr(line, index, count);
	return (0);
}

int	get_texs(char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (import_tex(2, 0, line));
	else if (!ft_strncmp(line, "SO", 2))
		return (import_tex(2, 1, line));
	else if (!ft_strncmp(line, "EA", 2))
		return (import_tex(2, 2, line));
	else if (!ft_strncmp(line, "WE", 2))
		return (import_tex(2, 3, line));
	else if (!ft_strncmp(line, "C", 1))
		return (import_tex(1, 4, line));
	else if (!ft_strncmp(line, "F", 1))
		return (import_tex(1, 5, line));
	else if (!ft_strncmp(line, "\n", 1))
		return (0);
	return (1);
}

static int	parse_rgb(char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		color;

	rgb = ft_split(line, ',');
	if (!rgb || ft_tablen(rgb) != 3)
	{
		if (rgb)
			ft_clear_tab(rgb);
		ft_clean_exit(get_data(), 1,
			"Error\nUnvalid ceiling or floor color");
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_clear_tab(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_clean_exit(get_data(), 1,
			"Error\nUnvalid ceiling or floor color");
	color = 0xFF000000 | (r << 16) | (g << 8) | b;
	return (color);
}

void	handle_sky_and_ground(t_data *data)
{
	int	c;

	if (data->tex[4].path)
	{
		c = parse_rgb(data->tex[4].path);
		data->ceiling_color = c;
	}
	else if (!data->sky_path)
	{
		data->sky_path = try_strdup("TEXTURES/spirale.xpm");
		if (!data->sky_path)
			ft_clean_exit(data, 1, "malloc failed for sky fallback path");
	}
	if (data->tex[5].path)
	{
		c = parse_rgb(data->tex[5].path);
		data->floor_color = c;
	}
	else
		data->floor_color = 0x444444;
}

int	read_texs(char ***map)
{
	int		i;
	t_data	*data;

	data = get_data();
	i = 0;
	while ((*map)[i] && (*map)[i][0] != '1' && (*map)[i][0] != ' '
		&& (*map)[i][0] != '0')
	{
		if (get_texs((*map)[i]))
			ft_clean_exit(data, 1, "unvalid elem before map");
		i++;
	}
	take_tex_out(map, i);
	handle_sky_and_ground(data);
	return (0);
}
