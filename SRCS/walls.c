/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:41:42 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/13 16:38:30 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

int	leak_check(char **map, int x, int y)
{
	if (map[y][x] == ' ' && ((y > 0 && map[y - 1][x] == '0')
		|| (map[y + 1] && map[y + 1][x] == '0')
		|| (x > 0 && map[y][x - 1] == '0')
		|| (map[y][x + 1] == '0')))
		return (1);
	return (0);
}

int	vertical_walls(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '1')
		return (1);
	while (line[i] && line[i] != ' ')
		i++;
	if (i > 0 && line[i - 1] != '1')
		return (1);
	return (0);
}
