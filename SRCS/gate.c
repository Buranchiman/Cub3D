/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gate.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillichien <chillichien@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 18:41:06 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/09 18:25:58 by chillichien      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	assign_gate_value(int x, int gate_tex,
		double gatedist, int texx_gate)
{
	t_data	*d;
	int		gi;

	d = get_data();
	if (d->gatecount[x] < d->doors_count)
	{
		gi = d->gatecount[x];
		d->gatelayers[x][gi].dist = gatedist;
		d->gatelayers[x][gi].texX = texx_gate;
		d->gatelayers[x][gi].locked = gate_tex;
		d->gatecount[x]++;
	}
}

void	calc_gate_area(t_data *d, t_tex *gatetex,
	int x, int gi)
{
	double	dist;

	dist = d->gatelayers[x][gi].dist;
	d->lineheight = (int)(SCRN_H / dist);
	d->drawstart = -d->lineheight / 2 + SCRN_H / 2 + d->pitch;
	if (d->drawstart < 0)
		d->drawstart = 0;
	d->drawend = d->lineheight / 2 + SCRN_H / 2 + d->pitch;
	if (d->drawend >= SCRN_H)
		d->drawend = SCRN_H - 1;
	d->texx = d->gatelayers[x][gi].texX;
	d->step = 1.0 * gatetex->height / d->lineheight;
	d->texpos = (d->drawstart - d->pitch - SCRN_H
			/ 2 + d->lineheight / 2) * d->step;
}

void	draw_gates(t_data *d, t_tex *gatetex, int x, double dist)
{
	int	y;

	y = d->drawstart;
	while (y < d->drawend)
	{
		d->texy = (int)d->texpos;
		d->texpos += d->step;
		if (d->texy < 0)
			d->texy = 0;
		if (d->texy >= gatetex->height)
			d->texy = gatetex->height - 1;
		d->color = gatetex->pixels[d->texy * gatetex->width + d->texx];
		if ((d->color & 0x00FFFFFF) != 0)
		{
			if (dist < d->pixeldepth[y][x])
			{
				put_px(d, x, y, d->color | 0xFF000000);
				d->pixeldepth[y][x] = dist;
			}
		}
		y++;
	}
}

void	door_back_to_front(t_data *d, int x, int count)
{
	t_tex	*gatetex;
	int		gi;
	double	dist;

	gi = count;
	while (gi >= 0)
	{
		dist = d->gatelayers[x][gi].dist;
		if (dist <= 0.0)
		{
			gi--;
			continue ;
		}
		gatetex = &d->tex[d->gatelayers[x][gi].locked];
		calc_gate_area(d, gatetex, x, gi);
		draw_gates(d, gatetex, x, dist);
		gi--;
	}
}

void	handle_gates(t_data *d)
{
	int		x;
	int		count;

	x = 0;
	while (x < SCRN_W)
	{
		count = d->gatecount[x];
		if (count <= 0)
		{
			x++;
			continue ;
		}
		door_back_to_front(d, x, count);
		x++;
	}
}
