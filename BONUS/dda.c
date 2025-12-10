/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillichien <chillichien@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:02:23 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/09 18:25:36 by chillichien      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	get_wallside(t_data *d)
{
	if (d->sidedistx < d->sidedisty)
	{
		d->sidedistx += d->deltadistx;
		d->mapx += d->stepx;
		d->side = 0;
		if (d->stepx == 1)
			d->cardinal = CARDEAST;
		else
			d->cardinal = CARDWEST;
	}
	else
	{
		d->sidedisty += d->deltadisty;
		d->mapy += d->stepy;
		d->side = 1;
		if (d->stepy == 1)
			d->cardinal = CARDNORTH;
		else
			d->cardinal = CARDSOUTH;
	}
}

void	hit_wall(t_data *d, int x)
{
	int		gate_tex;
	double	wallx;
	double	gatedist;
	int		texx_gate;

	if (door_is_locked_at(d, d->mapx, d->mapy))
		gate_tex = 13;
	else
		gate_tex = 14;
	if (d->side == 0)
		gatedist = d->sidedistx - d->deltadistx;
	else
		gatedist = d->sidedisty - d->deltadisty;
	if (d->side == 0)
		wallx = d->player_pos.y + gatedist * d->raydiry;
	else
		wallx = d->player_pos.x + gatedist * d->raydirx;
	wallx -= floor(wallx);
	texx_gate = (int)(wallx * (double)d->tex[gate_tex].width);
	if (texx_gate < 0)
		texx_gate = 0;
	if (texx_gate >= d->tex[gate_tex].width)
		texx_gate = d->tex[gate_tex].width - 1;
	assign_gate_value(x, gate_tex, gatedist, texx_gate);
}

void	perform_dda(t_data *d, int x)
{
	while (d->hit == 0)
	{
		get_wallside(d);
		if (d->map[d->mapy][d->mapx] == 'D')
		{
			hit_wall(d, x);
		}
		else if (d->map[d->mapy][d->mapx] == '1')
		{
			d->cardinal = fetch_tex(d->mapx, d->mapy);
			d->hit = 1;
		}
	}
}
