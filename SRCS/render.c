/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:34:59 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/12 14:31:17 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	door_to_close(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->doors_count)
	{
		if (data->tab_doors[i].to_closed == 1)
		{
			data->tab_doors[i].to_closed = 0;
			data->tab_doors[i].lock = 1;
		}
		i++;
	}
}

int	render_frame(void *param)
{
	t_data					*data;
	double					now;

	data = param;
	now = get_time();
	data->monster_time = (unsigned long)(now * 1000.0);
	data->deltatime = now - data->lasttime;
	data->lasttime = now;
	if (data->deltatime > 0.05)
		data->deltatime = 0.05;
	update_player(data);
	raycasting(data);
	display_minimap(data, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win_ptr, data->mlx_img->img, 0, 0);
	return (0);
}
