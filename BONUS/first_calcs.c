/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_calcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:01:32 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/12 14:31:36 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	first_calc(t_ray *r, t_data *d, int x)
{
	double	camx;

	camx = 2 * x / (double)SCRN_W - 1;
	r->raydirx = d->direction.x + d->cam.x * camx;
	r->raydiry = d->direction.y + d->cam.y * camx;
	r->mapx = (int)d->player_pos.x;
	r->mapy = (int)d->player_pos.y;
	if (r->raydirx == 0)
		r->deltadistx = 1e30;
	else
		r->deltadistx = fabs(1 / r->raydirx);
	if (r->raydiry == 0)
		r->deltadisty = 1e30;
	else
		r->deltadisty = fabs(1 / r->raydiry);
}

void	step_calc(t_ray *r, t_data *d)
{
	if (r->raydirx < 0)
	{
		r->stepx = -1;
		r->sidedistx = (d->player_pos.x - r->mapx) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->mapx + 1.0 - d->player_pos.x) * r->deltadistx;
	}
	if (r->raydiry < 0)
	{
		r->stepy = -1;
		r->sidedisty = (d->player_pos.y - r->mapy) * r->deltadisty;
	}
	else
	{
		r->stepy = 1;
		r->sidedisty = (r->mapy + 1.0 - d->player_pos.y) * r->deltadisty;
	}
}

void	calc_wall_drawing_area(t_ray *r, t_data *d)
{
	if (r->side == 0)
		r->perpwalldist = r->sidedistx - r->deltadistx;
	else
		r->perpwalldist = r->sidedisty - r->deltadisty;
	if (r->perpwalldist < 1e-6)
		r->perpwalldist = 1e-6;
	r->lineheight = (int)(SCRN_H / r->perpwalldist);
	r->drawstart = -r->lineheight / 2 + SCRN_H / 2 + d->pitch;
	if (r->drawstart < 0)
		r->drawstart = 0;
	r->drawend = r->lineheight / 2 + SCRN_H / 2 + d->pitch;
	if (r->drawend >= SCRN_H)
		r->drawend = SCRN_H - 1;
}
