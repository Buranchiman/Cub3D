/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:53:01 by mlemerci          #+#    #+#             */
/*   Updated: 2025/11/18 15:07:12 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

int	key_hook(int keycode, t_data *data)
{
	t_point	new_pos;

	if (!data->held_key)
		return (0);
	if (keycode == KEY_ESC)
		ft_clean_exit(data, 0, "See you soon👋");
	new_pos = data->player_pos;
	if ((keycode == KEY_W) || (keycode == KEY_UP))
		new_pos.y -= 0.5;
	else if ((keycode == KEY_S) || (keycode == KEY_DOWN))
		new_pos.y += 0.5;
	else if ((keycode == KEY_A) || (keycode == KEY_LEFT))
		new_pos.x -= 0.5;
	else if ((keycode == KEY_D) || (keycode == KEY_RIGHT))
		new_pos.x += 0.5;
	//⚜️bonus⚜️
	{
		if (data->map[(int)new_pos.y][(int)new_pos.x] == 'D')
		{
			int idx;

			idx = door_index_at(data, (int)new_pos.x, (int)new_pos.y);
			if (idx >= 0 && data->tab_doors && data->tab_doors[idx].lock)
			{
				if (open_door(data, idx) == 1)
				{
					data->player_pos = new_pos;
					mlx_clear_window(data->mlx_ptr, data->win_ptr);
					update_minimap(data);
				}
				return (0);
			}
		}
		if (data->map[(int)new_pos.y][(int)new_pos.x] != '1'
			&& !(data->map[(int)new_pos.y][(int)new_pos.x] == 'D'
			&& door_is_locked_at(data, new_pos.x, new_pos.y)))
		{
			data->player_pos = new_pos;
			mlx_clear_window(data->mlx_ptr, data->win_ptr);
			update_minimap(data);
		}
	}
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	data->held_key = keycode;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (data->held_key == keycode)
		data->held_key = 0;
	return (0);
}
