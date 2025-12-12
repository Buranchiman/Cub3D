/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:10:34 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/12 14:31:15 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	draw_ceiling(t_data *d, int x, t_ray *r, int drawstart)
{
	int	y;

	y = 0;
	while (y < drawstart)
	{
		if (d->sky.pixels && d->sky.width > 0 && d->sky.height > 0)
		{
			r->texx = (int)((double)x * d->sky.width / (double)SCRN_W);
			r->texy = (int)((double)y * d->sky.height / (double)SCRN_H);
			d->color = d->sky.pixels[r->texy * d->sky.width + r->texx];
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

double	calc_wallx(t_data *d, t_ray r)
{
	double	tmp;

	if (r.side == 0)
		tmp = d->player_pos.y + r.perpwalldist * r.raydiry;
	else
		tmp = d->player_pos.x + r.perpwalldist * r.raydirx;
	tmp -= floor((tmp));
	return (tmp);
}

int	raycasting(t_data *d)
{
	int		x;
	double	wallx;
	t_ray	r;

	x = 0;
	reset_gates(d);
	ft_bzero(&r, sizeof(t_ray));
	while (x < SCRN_W)
	{
		first_calc(&r, d, x);
		r.hit = 0;
		step_calc(&r, d);
		perform_dda(&r, d, x);
		calc_wall_drawing_area(&r, d);
		draw_ceiling(d, x, &r, r.drawstart);
		wallx = calc_wallx(d, r);
		walls_final_calc(d, &r, wallx);
		draw_walls(d, &r, x);
		x++;
	}
	handle_sprites(d, &r);
	handle_gates(d, &r);
	return (0);
}
