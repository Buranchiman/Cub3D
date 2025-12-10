/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gate.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 18:41:06 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/10 17:51:57 by wivallee         ###   ########.fr       */
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
		d->gatelayers[x][gi].texx = texx_gate;
		d->gatelayers[x][gi].locked = gate_tex;
		d->gatecount[x]++;
	}
}

static void	calc_gate_area(t_data *d, t_ray *r, t_gate_ctx *g)
{
	r->lineheight = (int)(SCRN_H / g->dist);
	r->drawstart = -r->lineheight / 2 + SCRN_H / 2 + d->pitch;
	if (r->drawstart < 0)
		r->drawstart = 0;
	r->drawend = r->lineheight / 2 + SCRN_H / 2 + d->pitch;
	if (r->drawend >= SCRN_H)
		r->drawend = SCRN_H - 1;
	r->texx = d->gatelayers[g->x][g->gi].texx;
	r->step = 1.0 * g->tex->height / r->lineheight;
	r->texpos = (r->drawstart - d->pitch
			- SCRN_H / 2 + r->lineheight / 2) * r->step;
}

// void	calc_gate_area(t_data *d, t_tex *gatetex,
// 	int x, int gi, t_ray *r)
// {
// 	double	dist;

// 	dist = d->gatelayers[x][gi].dist;
// 	r->lineheight = (int)(SCRN_H / dist);
// 	r->drawstart = -r->lineheight / 2 + SCRN_H / 2 + d->pitch;
// 	if (r->drawstart < 0)
// 		r->drawstart = 0;
// 	r->drawend = r->lineheight / 2 + SCRN_H / 2 + d->pitch;
// 	if (r->drawend >= SCRN_H)
// 		r->drawend = SCRN_H - 1;
// 	r->texx = d->gatelayers[x][gi].texx;
// 	r->step = 1.0 * gatetex->height / r->lineheight;
// 	r->texpos = (r->drawstart - d->pitch - SCRN_H
// 			/ 2 + r->lineheight / 2) * r->step;
// }

static void	draw_gates(t_data *d, t_ray *r, t_gate_ctx *g)
{
	int	y;

	y = r->drawstart;
	while (y < r->drawend)
	{
		r->texy = (int)r->texpos;
		r->texpos += r->step;
		if (r->texy < 0)
			r->texy = 0;
		if (r->texy >= g->tex->height)
			r->texy = g->tex->height - 1;
		d->color = g->tex->pixels[r->texy * g->tex->width + r->texx];
		if ((d->color & 0x00FFFFFF) != 0 && g->dist < d->pixeldepth[y][g->x])
		{
			put_px(d, g->x, y, d->color | 0xFF000000);
			d->pixeldepth[y][g->x] = g->dist;
		}
		y++;
	}
}

// void	draw_gates(t_data *d, t_tex *gatetex, int x, double dist, t_ray *r)
// {
// 	int	y;

// 	y = r->drawstart;
// 	while (y < r->drawend)
// 	{
// 		r->texy = (int)r->texpos;
// 		r->texpos += r->step;
// 		if (r->texy < 0)
// 			r->texy = 0;
// 		if (r->texy >= gatetex->height)
// 			r->texy = gatetex->height - 1;
// 		d->color = gatetex->pixels[r->texy * gatetex->width + r->texx];
// 		if ((d->color & 0x00FFFFFF) != 0)
// 		{
// 			if (dist < d->pixeldepth[y][x])
// 			{
// 				put_px(d, x, y, d->color | 0xFF000000);
// 				d->pixeldepth[y][x] = dist;
// 			}
// 		}
// 		y++;
// 	}
// }

static void	door_back_to_front(t_data *d, t_ray *r, int x, int count)
{
	t_gate_ctx	g;

	g.x = x;
	while (--count >= 0)
	{
		g.gi = count;
		g.dist = d->gatelayers[x][count].dist;
		if (g.dist <= 0.0)
			continue ;
		g.tex = &d->tex[d->gatelayers[x][count].locked];
		calc_gate_area(d, r, &g);
		draw_gates(d, r, &g);
	}
}

// void	door_back_to_front(t_data *d, int x, int count, t_ray *r)
// {
// 	t_tex	*gatetex;
// 	int		gi;
// 	double	dist;

// 	gi = count;
// 	while (gi >= 0)
// 	{
// 		dist = d->gatelayers[x][gi].dist;
// 		if (dist <= 0.0)
// 		{
// 			gi--;
// 			continue ;
// 		}
// 		gatetex = &d->tex[d->gatelayers[x][gi].locked];
// 		calc_gate_area(d, gatetex, x, gi, r);
// 		draw_gates(d, gatetex, x, dist, r);
// 		gi--;
// 	}

void	handle_gates(t_data *d, t_ray *r)
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
		door_back_to_front(d, r, x, count);
		x++;
	}
}
