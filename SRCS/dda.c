/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:02:23 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/10 15:49:43 by manon            ###   ########.fr       */
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

void	perform_dda(t_data *d)
{
	while (d->hit == 0)
	{
		get_wallside(d);
		if (d->map[d->mapy][d->mapx] == '1')
			d->hit = 1;
	}
}
