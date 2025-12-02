/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktexture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:43:02 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/01 02:04:40 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

int	import_texture(int index, int which, char *line)
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
		ft_clean_exit(get_data(), 1, "Error\nTexture format incorrect\n");
		return (1);
	}
	if (data->tex[which].path)
		free(data->tex[which].path);
	data->tex[which].path = ft_substr(line, index, count);
	return (0);
}

int	get_textures(char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (import_texture(3, 0, line));
	else if (!ft_strncmp(line, "SO ", 3))
		return (import_texture(3, 1, line));
	else if (!ft_strncmp(line, "EA ", 3))
		return (import_texture(3, 2, line));
	else if (!ft_strncmp(line, "WE ", 3))
		return (import_texture(3, 3, line));
	else if (!ft_strncmp(line, "C ", 2))
		return (import_texture(2, 4, line));
	else if (!ft_strncmp(line, "F ", 2))
		return (import_texture(2, 5, line));
	return (1);
}

void	take_texture_out(char ***map, int end)
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

int	read_textures(char ***map)
{
	int	i;
	t_data *data;

	data = get_data();
	i = 0;
	while ((*map)[i] && (*map)[i][0] != '1' && (*map)[i][0] != ' '
		&& (*map)[i][0] != '0')
	{
		if (get_textures((*map)[i]))
			return (1);
		i++;
	}
	take_texture_out(map, i);
	if (!data->tex[4].path && !data->sky_path)
	{
		data->sky_path = ft_strdup("TEXTURES/spirale.xpm");
		if (!data->sky_path)
			ft_clean_exit(data, 1, "malloc failed for sky fallback path");
	}
	return (0);
}
