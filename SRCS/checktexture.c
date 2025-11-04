/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktexture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:43:02 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/05 15:35:02 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	import_texture(int index, int which, char *line)
{
	int		count;
	t_data	*data;

	count = 0;
	while (line[index] == ' ')
		index++;
	while (line[index] && line[index] != ' ')
		count ++;
	if (line[count + index])
	{
		printf("Error\nTexture format incorrect\n");
		return (1);
	}
	if (data->texture[which])
		free(data->texture[which]);
	data->texture[which] = ft_substr(line, index, count);
	free(line);
	return (0);
}

int	get_textures(char *line)
{
	if (ft_strncmp(line, "NO ", 3))
		import_texture(3, 1, line);
	else if (ft_strncmp(line, "SO ", 3))
		import_texture(3, 2, line);
	else if (ft_strncmp(line, "EA ", 3))
		import_texture(3, 3, line);
	else if (ft_strncmp(line, "WE ", 3))
		import_texture(3, 4, line);
	else if (ft_strncmp(line, "C ", 3))
		import_texture(3, 5, line);
	else if (ft_strncmp(line, "F ", 3))
		import_texture(3, 6, line);
}

void	take_texture_out(char ***map, int end)
{
	int		i;
	char	*temp;

	i = 0;
	temp = **map;
	while (i < end)
	{
		free(temp[i]);
		// il faut reallouer un tableau plus petit pour enlever les premieres lignes
	}
}

int	read_textures(char ***map)
{
	int	i;

	i = 0;
	while (*map[i] && *map[i][1] != '1')
	{
		get_textures(*map[i]);
		i++;
	}
}
