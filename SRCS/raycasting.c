/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:10:34 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/10 17:40:36 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	draw_ceiling(t_data *d, int x)
{
	int	y;

	y = 0;
	while (y < d->drawstart)
	{
		if (d->sky.pixels && d->sky.width > 0 && d->sky.height > 0)
		{
			d->texx = (int)((double)x * d->sky.width / (double)SCRN_W);
			d->texy = (int)((double)y * d->sky.height / (double)SCRN_H);
			d->color = d->sky.pixels[d->texy * d->sky.width + d->texx];
			put_px(d, x, y, d->color | 0xFF000000);
		}
		else
			put_px(d, x, y, d->ceiling_color);
		y++;
	}
}

void	reset_gates(t_data *d)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < SCRN_W)
	{
		d->gatecount[i] = 0;
		i++;
	}
	y = 0;
	while (y < SCRN_H)
	{
		x = 0;
		while (x < SCRN_W)
		{
			d->pixeldepth[y][x] = 1e30;
			x++;
		}
		y++;
	}
}

int	raycasting(t_data *d)
{
	int		x;
	double	wallx;

	x = 0;
	reset_gates(d);
	while (x < SCRN_W)
	{
		first_calc(d, x);
		d->hit = 0;
		step_calc(d);
		perform_dda(d);
		calc_wall_drawing_area(d);
		draw_ceiling(d, x);
		if (d->side == 0)
			wallx = d->player_pos.y + d->perpwalldist * d->raydiry;
		else
			wallx = d->player_pos.x + d->perpwalldist * d->raydirx;
		wallx -= floor((wallx));
		walls_final_calc(d, wallx);
		draw_walls(d, x);
		x++;
	}
	handle_sprites(d);
	handle_gates(d);
	return (0);
}

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
	mouse_rotation(data);
	raycasting(data);
	display_minimap(data, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win_ptr, data->mlx_img->img, 0, 0);
	return (0);
}
