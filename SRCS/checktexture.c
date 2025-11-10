/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktexture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:43:02 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/10 14:09:33 by mlemerci         ###   ########.fr       */
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
		printf("Error\nTexture format incorrect\n");
		return (1);
	}
	if (data->texture[which].path)
	{
		free(data->texture[which].path);
		//data->texture[which].path = NULL;
	}
	data->texture[which].path = ft_substr(line, index, count);
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

//void	display_texture() // fonction de debuggage
//{
//	int		i;
//	t_data	*data;
//
//	i = 0;
//	data = get_data();
//	while (i < 9)
//	{
//		printf("texture are: %s\n", data->texture[i].path);
//		i++;
//	}
//}

int	read_textures(char ***map)
{
	int	i;

	i = 0;
	while ((*map)[i] && (*map)[i][0] != '1' && (*map)[i][0] != ' '
		&& (*map)[i][0] != '0')
	//while ((*map)[i])
	{
		printf("line is %s\n", (*map)[i]);
		if (get_textures((*map)[i]))
			return (1);
		i++;
	}
	printf("%d textures have been read\n", i);
	//display_texture();
	take_texture_out(map, i);
	// i = 0;
	// printf("MAP IS :\n");
	// while (get_data()->map[i])
	// {
	// 	ft_printf(1, "%s\n", get_data()->map[i]);
	// 	i++;
	// }
	return (0);
}
