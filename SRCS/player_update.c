/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:00:00 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/03 15:46:52 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

static void	rotate_player_left(t_data *d, double rs)
{
	double	odx;
	double	ody;
	double	opx;
	double	opy;

	odx = d->direction.x;
	ody = d->direction.y;
	opx = d->cam.x;
	opy = d->cam.y;
	d->direction.x = odx * cos(-rs) - ody * sin(-rs);
	d->direction.y = odx * sin(-rs) + ody * cos(-rs);
	d->cam.x = opx * cos(-rs) - opy * sin(-rs);
	d->cam.y = opx * sin(-rs) + opy * cos(-rs);
}

static void	rotate_player_right(t_data *d, double rs)
{
	double	odx;
	double	ody;
	double	opx;
	double	opy;

	odx = d->direction.x;
	ody = d->direction.y;
	opx = d->cam.x;
	opy = d->cam.y;
	d->direction.x = odx * cos(rs) - ody * sin(rs);
	d->direction.y = odx * sin(rs) + ody * cos(rs);
	d->cam.x = opx * cos(rs) - opy * sin(rs);
	d->cam.y = opx * sin(rs) + opy * cos(rs);
}


static void	rotate_player(t_data *d)
{
	double	rs;

	rs = 3.0 * d->deltatime;
	if (d->keys.left)
		rotate_player_left(d, rs);
	if (d->keys.right)
		rotate_player_right(d, rs);
}

static t_point	move_player(t_data *d, double ms)
{
	t_point	tmp;

	tmp.x = d->player_pos.x;
	tmp.y = d->player_pos.y;
	if (d->keys.w)
	{
		d->player_pos.x += d->direction.x * ms;
		d->player_pos.y += d->direction.y * ms;
	}
	if (d->keys.s)
	{
		d->player_pos.x -= d->direction.x * ms;
		d->player_pos.y -= d->direction.y * ms;
	}
	if (d->keys.d)
	{
		d->player_pos.x += -d->direction.y * ms;
		d->player_pos.y += d->direction.x * ms;
	}
	if (d->keys.a)
	{
		d->player_pos.x += d->direction.y * ms;
		d->player_pos.y += -d->direction.x * ms;
	}
	return (tmp);
}

void	update_player(t_data *d)
{
	double	ms;
	t_point	tmp;
	int		idx;

	ms = 2.0 * d->deltatime;
	rotate_player(d);
	tmp = move_player(d, ms);
	if (d->map[(int)tmp.y][(int)tmp.x] == 'D')
	{
		idx = door_index_at(d, (int)tmp.x, (int)tmp.y);
		if (idx >= 0 && d->tab_doors)// && d->tab_doors[idx].lock)
			open_door(d, idx);
	}
	if (d->map[(int)d->player_pos.y][(int)d->player_pos.x] == '1'
		|| (d->map[(int)d->player_pos.y][(int)d->player_pos.x] == 'D'
		&& door_is_locked_at(d, (int)tmp.x, (int)tmp.y)))
	{
		d->player_pos.x = tmp.x;
		d->player_pos.y = tmp.y;
	}
}
