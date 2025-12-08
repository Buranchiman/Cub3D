/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_calcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:01:32 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/08 15:01:32 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	first_calc(t_data *d, int x)
{
	double	camx;

	camx = 2 * x / (double)SCRN_W - 1;
	d->raydirx = d->direction.x + d->cam.x * camx;
	d->raydiry = d->direction.y + d->cam.y * camx;
	d->mapx = (int)d->player_pos.x;
	d->mapy = (int)d->player_pos.y;
	if (d->raydirx == 0)
		d->deltadistx = 1e30;
	else
		d->deltadistx = fabs(1 / d->raydirx);
	if (d->raydiry == 0)
		d->deltadisty = 1e30;
	else
		d->deltadisty = fabs(1 / d->raydiry);
}

void	step_calc(t_data *d)
{
	if (d->raydirx < 0)
	{
		d->stepx = -1;
		d->sidedistx = (d->player_pos.x - d->mapx) * d->deltadistx;
	}
	else
	{
		d->stepx = 1;
		d->sidedistx = (d->mapx + 1.0 - d->player_pos.x) * d->deltadistx;
	}
	if (d->raydiry < 0)
	{
		d->stepy = -1;
		d->sidedisty = (d->player_pos.y - d->mapy) * d->deltadisty;
	}
	else
	{
		d->stepy = 1;
		d->sidedisty = (d->mapy + 1.0 - d->player_pos.y) * d->deltadisty;
	}
}

void	calc_wall_drawing_area(t_data *d)
{
	if (d->side == 0)
		d->perpwalldist = (d->sidedistx - d->deltadistx);
	else
		d->perpwalldist = (d->sidedisty - d->deltadisty);
	 //Calculate height of line to draw on screen
	if (d->perpwalldist < 1e-6)
		d->perpwalldist = 1e-6;
	d->lineheight = (int)(SCRN_H / d->perpwalldist);
	//calculate lowest and highest pixel to fill in current stripe
	d->drawstart = -d->lineheight / 2 + SCRN_H / 2 + d->pitch;
	if (d->drawstart < 0)
		d->drawstart = 0;
	d->drawend = d->lineheight / 2 + SCRN_H / 2 + d->pitch;
	if (d->drawend >= SCRN_H)
		d->drawend = SCRN_H - 1;
}
