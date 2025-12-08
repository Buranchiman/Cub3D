/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:59:50 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/08 15:07:45 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	walls_final_calc(t_data *d, double wallx)
{
	 //x coordinate on the tex
	d->texx = (int)(wallx * (double)d->tex[d->cardinal].width);
	if (d->side == 0 && d->raydirx > 0)
		d->texx = d->tex[d->cardinal].width - d->texx - 1;
	if (d->side == 1 && d->raydiry < 0)
		d->texx = d->tex[d->cardinal].width - d->texx - 1;
	 // TODO: an integer-only bresenham or DDA like algorithm could make the tex coordinate stepping faster
	// How much to increase the tex coordinate per screen pixel
	d->step = 1.0 * d->tex[d->cardinal].height / d->lineheight;
	// Starting tex coordinate
	d->texpos = (d->drawstart - d->pitch - SCRN_H / 2 + d->lineheight / 2) * d->step;
}

void	draw_walls(t_data *d, int x)
{
	int	y;

	y = 0;
	y = d->drawstart;
	while (y < d->drawend)
	{
		// Cast the tex coordinate to integer, and mask with (TEXHEIGHT - 1) in case of overflow
		d->texy = (int)d->texpos & (d->tex[d->cardinal].height - 1);
		d->texpos += d->step;
		d->color = d->tex[d->cardinal].pixels[d->texy
			* d->tex[d->cardinal].width + d->texx];
		// unsigned int d->color = 0xFF0000FF;
		//make d->color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// if(d->side == 1) d->color = (d->color >> 1) & 8355711;
		put_px(d, x, y, d->color | 0xFF000000);
		d->pixeldepth[y][x] = d->perpwalldist;   // wall is at this distance
		y++;
	}
	while (y < SCRN_H)
	{
		put_px(d, x, y, FLOOR_COLOR);
		y++;
	}
}
