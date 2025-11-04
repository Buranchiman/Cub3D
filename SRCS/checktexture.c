/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktexture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:43:02 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/04 17:03:26 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	import_texture(int index, int which, char *line)
{
	int	count;

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

	return (0);
}

int	get_textures(char *line)
{
	if (ft_strncmp(line, "NO ", 3))
		import_texture(data, 3);

}

int	read_textures(char **map)
{
	int	i;

	i = 0;
	while (map[i] && map[i][1] != '1')
	{
		get
	}
}
