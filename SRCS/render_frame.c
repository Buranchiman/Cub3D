/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:55:46 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/02 14:56:00 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	render_frame(void *param)
{
	t_data			*data;
	double			now;
	unsigned long	now_ms;

	(void)param;
	data = get_data();
	now = get_time();
	data->deltatime = now - data->lasttime;
	data->lasttime = now;
	now_ms = (unsigned long)(now * 1000.0);
	if (now_ms - data->last_update >= 120UL)
	{
		monsters_move(data);
		data->last_update = now_ms;
	}
	if (data->deltatime > 0.05)
		data->deltatime = 0.05;
	mouse_rotation(data);
	update_player(data);
	raycasting(data);
	// compose minimap into the main image buffer, then blit once
	display_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->mlx_img->img, 0, 0);
	return (0);
}
