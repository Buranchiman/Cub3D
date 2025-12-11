/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_calcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:01:32 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/11 14:41:14 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	first_calc(t_data *d, int x)
{
	double	camx;

	camx = 2 * x / (double)SCRN_W - 1;
	d->raydirx = d->direction.x + d->cam.x * camx;
	d->raydiry = d->direction.y + d->cam.y * camx;
	r->mapx = (int)d->player_pos.x;
	r->mapy = (int)d->player_pos.y;
	if (d->raydirx == 0)
		r->deltadistx = 1e30;
	else
		r->deltadistx = fabs(1 / d->raydirx);
	if (d->raydiry == 0)
		r->deltadisty = 1e30;
	else
		r->deltadisty = fabs(1 / d->raydiry);
}

void	step_calc(t_data *d)
{
	if (d->raydirx < 0)
	{
		r->stepx = -1;
		r->sidedistx = (d->player_pos.x - r->mapx) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->mapx + 1.0 - d->player_pos.x) * r->deltadistx;
	}
	if (d->raydiry < 0)
	{
		d->stepy = -1;
		r->sidedisty = (d->player_pos.y - r->mapy) * r->deltadisty;
	}
	else
	{
		d->stepy = 1;
		r->sidedisty = (r->mapy + 1.0 - d->player_pos.y) * r->deltadisty;
	}
}

void	calc_wall_drawing_area(t_data *d)
{
	if (r->side == 0)
		d->perpwalldist = (r->sidedistx - r->deltadistx);
	else
		d->perpwalldist = (r->sidedisty - r->deltadisty);
	if (d->perpwalldist < 1e-6)
		d->perpwalldist = 1e-6;
	d->lineheight = (int)(SCRN_H / d->perpwalldist);
	d->drawstart = -d->lineheight / 2 + SCRN_H / 2 + d->pitch;
	if (d->drawstart < 0)
		d->drawstart = 0;
	d->drawend = d->lineheight / 2 + SCRN_H / 2 + d->pitch;
	if (d->drawend >= SCRN_H)
		d->drawend = SCRN_H - 1;
}
