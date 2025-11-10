/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:42:04 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/10 15:18:59 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	init_data(void)
{
	static t_data	*data;
	int i;

	i = 0;
	data = get_data();
	data->buffer = NULL;
	data->map = NULL;
	data->player_pos.x = -1;
	data->player_pos.y = -1;
	data->cameraplane.x = 0;
	data->cameraplane.y = 0.66;
	data->direction.x = 0;
	data->direction.y = 0;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	//a adapter👇
	while (i <= 9)
	{
		data->texture[i].path = NULL;
		data->texture[i].ptr = NULL;
		//data->texture[i].width = 32;
		//data->texture[i].height = 32;
		i++;
	}
}
