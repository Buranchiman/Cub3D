/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:59:50 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/11 14:37:40 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	walls_final_calc(t_data *d, double wallx)
{
	d->texx = (int)(wallx * (double)d->tex[d->cardinal].width);
	if (r->side == 0 && d->raydirx > 0)
		d->texx = d->tex[d->cardinal].width - d->texx - 1;
	if (r->side == 1 && d->raydiry < 0)
		d->texx = d->tex[d->cardinal].width - d->texx - 1;
	d->step = 1.0 * d->tex[d->cardinal].height / d->lineheight;
	d->texpos = (d->drawstart - d->pitch
			- SCRN_H / 2 + d->lineheight / 2) * d->step;
}

void	draw_walls(t_data *d, int x)
{
	int	y;

	y = 0;
	y = d->drawstart;
	while (y < d->drawend)
	{
		d->texy = (int)d->texpos & (d->tex[d->cardinal].height - 1);
		d->texpos += d->step;
		d->color = d->tex[d->cardinal].pixels[d->texy
			* d->tex[d->cardinal].width + d->texx];
		put_px(d, x, y, d->color | 0xFF000000);
		d->pixeldepth[y][x] = d->perpwalldist;
		y++;
	}
	while (y < SCRN_H)
	{
		put_px(d, x, y, d->floor_color);
		y++;
	}
}
