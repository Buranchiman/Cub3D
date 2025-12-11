/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:02:23 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/11 15:44:24 by wivallee         ###   ########.fr       */
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

void	perform_dda(t_ray *r, t_data *d, int x)
{
	(void)x;
	while (r->hit == 0)
	{
		get_wallside(r, d);
		if (d->map[r->mapy][r->mapx] == '1')
			r->hit = 1;
	}
}
