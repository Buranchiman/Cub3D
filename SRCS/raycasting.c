/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillichien <chillichien@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:10:34 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/08 11:50:55 by chillichien      ###   ########.fr       */
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
			put_px(d, x, y, CEILING_COLOR);
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
		d->gateCount[i] = 0;
		i++;
	}
	y = 0;
	while (y < SCRN_H)
	{
		x = 0;
		while (x < SCRN_W)
		{
			d->pixelDepth[y][x] = 1e30;
			x++;
		}
		y++;
	}
}

int	raycasting(t_data *d)
{
	int		x;
	double	wallx; //where exactly the wall was d->hit

	x = 0;
	// reset gate counts for this frame
	reset_gates(d);
	while (x < SCRN_W)
	{
		first_calc(d, x);
		 //calculate d->step and initial sideDist
		//perform DDA
		d->hit = 0;
		step_calc(d);
		perform_dda(d, x);
		calc_wall_drawing_area(d);
		draw_ceiling(d, x);
		 //calculate value of wallx
		if (d->side == 0)
			wallx = d->player_pos.y + d->perpwalldist * d->raydiry;
		else
			wallx = d->player_pos.x + d->perpwalldist * d->raydirx;
		wallx -= floor((wallx));
		 //x coordinate on the tex
		walls_final_calc(d, wallx);
		draw_walls(d, x);
		x++;
	}
	handle_sprites(d);
	handle_gates(d);
	return (0);
}

// compose minimap into the main image buffer, then blit once
int	render_frame(void *param)
{
	t_data			*d;
	double			now;
	unsigned long	now_ms;

	(void)param;
	d = get_data();
	now = get_time();
	d->deltatime = now - d->lasttime;
	d->lasttime = now;
	now_ms = (unsigned long)(now * 1000.0);
	if (now_ms - d->last_update >= 120UL)
	{
		monsters_move(d);
		d->last_update = now_ms;
	}
	if (d->deltatime > 0.05)
		d->deltatime = 0.05;
	mouse_rotation(d);
	update_player(d);
	raycasting(d);
	display_minimap(d, 0, 0);
	mlx_put_image_to_window(d->mlx_ptr,
		d->win_ptr, d->mlx_img->img, 0, 0);
	return (0);
}
