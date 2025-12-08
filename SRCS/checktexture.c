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
	if (!ft_strncmp(line, "NO ", 3))
		return (import_tex(3, 0, line));
	else if (!ft_strncmp(line, "SO ", 3))
		return (import_tex(3, 1, line));
	else if (!ft_strncmp(line, "EA ", 3))
		return (import_tex(3, 2, line));
	else if (!ft_strncmp(line, "WE ", 3))
		return (import_tex(3, 3, line));
	else if (!ft_strncmp(line, "C ", 2))
		return (import_tex(2, 4, line));
	else if (!ft_strncmp(line, "F ", 2))
		return (import_tex(2, 5, line));
	return (1);
}

//AAA
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
		return (-1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_clear_tab(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	color = 0xFF000000 | (r << 16) | (g << 8) | b;
	return (color);
}

void	take_tex_out(char ***map, int end)
{
	int		i;
	char	**temp;

	i = 0;
	temp = *map;
	while (i < end)
	{
		free(temp[i]);
		i++;
	}
	ft_memmove(*map, &temp[i], (ft_tablen(&temp[i]) + 1) * sizeof(char *));
}

int	read_texs(char ***map)
{
	int	i;
	t_data *data;
	int c;

	data = get_data();
	i = 0;
	while ((*map)[i] && (*map)[i][0] != '1' && (*map)[i][0] != ' '
		&& (*map)[i][0] != '0')
	{
		if (get_texs((*map)[i]))
			return (1);
		i++;
	}
	take_tex_out(map, i);
	//AAA
	if (data->tex[4].path)
	{
		c = parse_rgb(data->tex[4].path);
		//if (c == -1)
		//	ft_clean_exit(data, 1, "Invalid ceiling color");
		data->ceiling_color = c;
	}
	else if (!data->sky_path)
	{
		data->sky_path = ft_strdup("TEXTURES/spirale.xpm");
		if (!data->sky_path)
			ft_clean_exit(data, 1, "malloc failed for sky fallback path");
	}
	if (data->tex[5].path)
	{
		c = parse_rgb(data->tex[5].path);
		//if (c == -1)
		//	ft_clean_exit(data, 1, "Invalid floor color");
		data->floor_color = c;
	}
	else
		data->floor_color = 0x444444;
	return (0);
}

//	take_tex_out(map, i);
//	if (!data->tex[4].path && !data->sky_path)
//	{
//		data->sky_path = ft_strdup("TEXTURES/spirale.xpm");
//		if (!data->sky_path)
//			ft_clean_exit(data, 1, "malloc failed for sky fallback path");
//	}
//	return (0);
//}
