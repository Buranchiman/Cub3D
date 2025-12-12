/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:02:23 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/12 14:31:33 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	get_wallside(t_ray *r, t_data *d)
{
	if (r->sidedistx < r->sidedisty)
	{
		r->sidedistx += r->deltadistx;
		r->mapx += r->stepx;
		r->side = 0;
		if (r->stepx == 1)
			d->cardinal = CARDEAST;
		else
			d->cardinal = CARDWEST;
	}
	else
	{
		r->sidedisty += r->deltadisty;
		r->mapy += r->stepy;
		r->side = 1;
		if (r->stepy == 1)
			d->cardinal = CARDSOUTH;
		else
			d->cardinal = CARDNORTH;
	}
}

void	hit_wall(t_ray *r, t_data *d, int x)
{
	int		gate_tex;
	double	wallx;
	double	gatedist;
	int		texx_gate;

	if (door_is_locked_at(d, r->mapx, r->mapy))
		gate_tex = 13;
	else
		gate_tex = 14;
	if (r->side == 0)
		gatedist = r->sidedistx - r->deltadistx;
	else
		gatedist = r->sidedisty - r->deltadisty;
	if (r->side == 0)
		wallx = d->player_pos.y + gatedist * r->raydiry;
	else
		wallx = d->player_pos.x + gatedist * r->raydirx;
	wallx -= floor(wallx);
	texx_gate = (int)(wallx * (double)d->tex[gate_tex].width);
	if (texx_gate < 0)
		texx_gate = 0;
	if (texx_gate >= d->tex[gate_tex].width)
		texx_gate = d->tex[gate_tex].width - 1;
	assign_gate_value(x, gate_tex, gatedist, texx_gate);
}

void	perform_dda(t_ray *r, t_data *d, int x)
{
	while (r->hit == 0)
	{
		get_wallside(r, d);
		if (d->map[r->mapy][r->mapx] == 'D')
		{
			hit_wall(r, d, x);
		}
		else if (d->map[r->mapy][r->mapx] == '1')
		{
			d->cardinal = fetch_tex(r->mapx, r->mapy);
			r->hit = 1;
		}
	}
}
