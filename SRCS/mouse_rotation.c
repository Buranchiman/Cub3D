/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:00:00 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/02 15:14:00 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	mouse_rotation(t_data *data)
{
	int		dx;
	double	rot;
	double	c;
	double	s;
	double	odx;
	double	ody;
	double	opx;
	double	opy;

	dx = data->mouse_dx;
	data->mouse_dx = 0;
	rot = dx * data->mouse_sens;
	if (rot > data->max_rot_frame)
		rot = data->max_rot_frame;
	if (rot < -data->max_rot_frame)
		rot = -data->max_rot_frame;
	if (rot == 0.0)
		return ;
	c = cos(rot);
	s = sin(rot);
	odx = data->direction.x;
	ody = data->direction.y;
	opx = data->cam.x;
	opy = data->cam.y;
	data->direction.x = odx * c - ody * s;
	data->direction.y = odx * s + ody * c;
	data->cam.x = opx * c - opy * s;
	data->cam.y = opx * s + opy * c;
}
