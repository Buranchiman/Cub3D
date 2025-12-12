/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_monsters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:01:28 by manon             #+#    #+#             */
/*   Updated: 2025/12/12 14:31:26 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

int	monster_count(t_data *data, int x, int y)
{
	int	monsters_count;

	monsters_count = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'M')
				monsters_count++;
			x++;
		}
		y++;
	}
	if (monsters_count > 0)
	{
		data->tab_m = ft_calloc(monsters_count, sizeof(*(data->tab_m)));
		if (!data->tab_m)
			ft_clean_exit(data, 1, "Malloc failed in monster_count");
		data->monster_count = monsters_count;
	}
	else
		data->tab_m = NULL;
	return (monsters_count);
}

void	monster_init(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	if (!monster_count(data, 0, 0))
		return ;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'M')
			{
				data->tab_m[i].pos.x = (double)x;
				data->tab_m[i].pos.y = (double)y;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	valid_moves(t_data *data, t_point tab_tmp, int i, int j)
{
	int	tx;
	int	ty;

	tx = (int)tab_tmp.x;
	ty = (int)tab_tmp.y;
	if (ty < 0 || ty >= (int)ft_tablen(data->map) || tx < 0
		|| tx >= (int)ft_strlen(data->map[ty]))
		return ;
	if (data->map[ty][tx] == '1' || (data->map[ty][tx] == 'D'
		&& door_is_locked_at(data, tab_tmp.x, tab_tmp.y)))
		return ;
	while (data->tab_m && j < data->monster_count)
	{
		if (j != i && (int)data->tab_m[j].pos.x == tx
			&& (int)data->tab_m[j].pos.y == ty)
			return ;
		j++;
	}
	data->map[(int)data->tab_m[i].pos.y][(int)data->tab_m[i].pos.x] = '0';
	data->tab_m[i].pos.x = tab_tmp.x;
	data->tab_m[i].pos.y = tab_tmp.y;
	data->map[(int)data->tab_m[i].pos.y][(int)data->tab_m[i].pos.x] = 'M';
	if (fabs(data->player_pos.x - data->tab_m[i].pos.x) < 0.3
		&& fabs(data->player_pos.y - data->tab_m[i].pos.y) < 0.3)
		ft_clean_exit(data, 0, "YOU'RE DEAD!💀");
}

void	monsters_move(t_data *data)
{
	int		i;
	t_point	tab_tmp;

	i = 0;
	if (!data->tab_m || data->monster_count == 0)
		return ;
	while (i < data->monster_count)
	{
		tab_tmp.x = data->tab_m[i].pos.x;
		tab_tmp.y = data->tab_m[i].pos.y;
		if ((data->player_pos.x - data->tab_m[i].pos.x) < 0)
			tab_tmp.x = data->tab_m[i].pos.x - 0.1;
		else if ((data->player_pos.x - data->tab_m[i].pos.x) > 0)
			tab_tmp.x = data->tab_m[i].pos.x + 0.1;
		if ((data->player_pos.y - data->tab_m[i].pos.y) < 0)
			tab_tmp.y = data->tab_m[i].pos.y - 0.1;
		else if ((data->player_pos.y - data->tab_m[i].pos.y) > 0)
			tab_tmp.y = data->tab_m[i].pos.y + 0.1;
		valid_moves(data, tab_tmp, i, 0);
		i++;
	}
}
