/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:59:50 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/12 14:31:54 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	walls_final_calc(t_data *d, t_ray *r, double wallx)
{
	r->texx = (int)(wallx * (double)d->tex[d->cardinal].width);
	if (r->side == 0 && r->raydirx < 0)
		r->texx = d->tex[d->cardinal].width - r->texx - 1;
	if (r->side == 1 && r->raydiry > 0)
		r->texx = d->tex[d->cardinal].width - r->texx - 1;
	r->step = 1.0 * d->tex[d->cardinal].height / r->lineheight;
	r->texpos = (r->drawstart - d->pitch
			- SCRN_H / 2 + r->lineheight / 2) * r->step;
}

void	draw_walls(t_data *d, t_ray *r, int x)
{
	int	y;

	y = 0;
	y = r->drawstart;
	while (y < r->drawend)
	{
		r->texy = (int)r->texpos & (d->tex[d->cardinal].height - 1);
		r->texpos += r->step;
		d->color = d->tex[d->cardinal].pixels[r->texy
			* d->tex[d->cardinal].width + r->texx];
		put_px(d, x, y, d->color | 0xFF000000);
		d->pixeldepth[y][x] = r->perpwalldist;
		y++;
	}
	while (y < SCRN_H)
	{
		put_px(d, x, y, d->floor_color);
		y++;
	}
}
