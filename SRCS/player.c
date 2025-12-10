/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 18:23:40 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/10 15:42:58 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

int	get_player(char **map, int i, int j)
{
	t_data	*data;
	char	c;

	data = get_data();
	c = map[j][i];
	if (ft_strchr("NSWE", c))
	{
		data->player_pos.x = i + 0.5;
		data->player_pos.y = j + 0.5;
		map[j][i] = '0';
		set_direction(c, data);
		return (1);
	}
	return (0);
}

void	mouse_rotation(t_data *d)
{
	int		dx;
	double	rot;
	double	c;
	double	s;
	double	old_dir;

	dx = d->mouse_dx;
	d->mouse_dx = 0;
	rot = dx * d->mouse_sens;
	if (rot > d->max_rot_frame)
		rot = d->max_rot_frame;
	if (rot < -d->max_rot_frame)
		rot = -d->max_rot_frame;
	if (rot != 0.0)
	{
		c = cos(rot);
		s = sin(rot);
		old_dir = d->direction.x;
		d->direction.x = d->direction.x * c - d->direction.y * s;
		d->direction.y = old_dir * s + d->direction.y * c;
		d->cam.y = d->cam.x * s + d->cam.y * c;
		d->cam.x = d->cam.x * c - d->cam.y * s;
	}
	update_player(d);
}

static void	rotate_player(t_data *d)
{
	double	old_dir;
	double	old_plan;
	double	rotspeed;

	rotspeed = 3.0 * d->deltatime;
	old_dir = d->direction.x;
	old_plan = d->cam.x;
	if (d->keys.left)
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
	t_point	tmp;

	movespeed = 2.0 * d->deltatime;
	rotate_player(d);
	tmp = move_player(d, movespeed);
	if (d->map[(int)d->player_pos.y][(int)d->player_pos.x] == '1')
	{
		d->player_pos.x = tmp.x;
		d->player_pos.y = tmp.y;
	}
}
