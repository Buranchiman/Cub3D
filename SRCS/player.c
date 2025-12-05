/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 18:23:40 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/05 18:25:31 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

static void	rotate_player(t_data *d)
{
	double	old_dir;
	double	old_plan;
	double	rotspeed;

	rotspeed = 3.0 * d->deltatime;
	old_dir = d->direction.x;
	old_plan = d->cam.x;
	if (d->keys.left) //j'ai inverse les touches (peut-etre a investiguer plus en profondeur)
	{
		d->direction.x = d->direction.x * cos(-rotspeed)
			- d->direction.y * sin(-rotspeed);
		d->direction.y = old_dir * sin(-rotspeed)
			+ d->direction.y * cos(-rotspeed);
		d->cam.x = d->cam.x * cos(-rotspeed) - d->cam.y * sin(-rotspeed);
		d->cam.y = old_plan * sin(-rotspeed) + d->cam.y * cos(-rotspeed);
	}
	if (d->keys.right)
	{
		d->direction.x = d->direction.x * cos(rotspeed)
			- d->direction.y * sin(rotspeed);
		d->direction.y = old_dir * sin(rotspeed)
			+ d->direction.y * cos(rotspeed);
		d->cam.x = d->cam.x * cos(rotspeed) - d->cam.y * sin(rotspeed);
		d->cam.y = old_plan * sin(rotspeed) + d->cam.y * cos(rotspeed);
	}
}

static t_point	move_player(t_data *d, double movespeed)
{
	t_point	tmp;

	tmp.x = d->player_pos.x;
	tmp.y = d->player_pos.y;
	if (d->keys.w)
	{
		d->player_pos.x += d->direction.x * movespeed;
		d->player_pos.y += d->direction.y * movespeed;
	}
	if (d->keys.s)
	{
		d->player_pos.x -= d->direction.x * movespeed;
		d->player_pos.y -= d->direction.y * movespeed;
	}
	if (d->keys.d)
	{
		d->player_pos.x += -d->direction.y * movespeed;
		d->player_pos.y += d->direction.x * movespeed;
	}
	if (d->keys.a)
	{
		d->player_pos.x += d->direction.y * movespeed;
		d->player_pos.y += -d->direction.x * movespeed;
	}
	return (tmp);
}

void	update_player(t_data *d)
{
	double	movespeed;
	int		idx;
	t_point	tmp;

	movespeed = 2.0 * d->deltatime;
	rotate_player(d);
	tmp = move_player(d, movespeed);
	if (d->map[(int)tmp.y][(int)tmp.x] == 'D')
	{
		idx = door_index_at(d, (int)tmp.x, (int)tmp.y);
		if (idx >= 0 && d->tab_doors && d->tab_doors[idx].lock)
			open_door(d, idx);
	}
	if (d->map[(int)d->player_pos.y][(int)d->player_pos.x] == '1'
	|| (d->map[(int)d->player_pos.y][(int)d->player_pos.x] == 'D'
 		&& door_is_locked_at(d, (int)tmp.x, (int)tmp.y))) //peut-etre a modifier si ca ram comme ne pas "rollback" mais modifier directement le tmp et si c'est bon l'assigner
	{
		d->player_pos.x = tmp.x;
		d->player_pos.y = tmp.y;
	}
}
