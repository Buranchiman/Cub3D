/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:53:01 by mlemerci          #+#    #+#             */
/*   Updated: 2025/11/19 17:30:59 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

// int	key_hook(int keycode, t_data *data)
// {
// 	t_point	new_pos;

// 	if (!data->held_key)
// 		return (0);
// 	new_pos = data->player_pos;
// 	//bonus⚜️
// 	if (data->map[(int)new_pos.y][(int)new_pos.x] == 'D')
// 	{
// 		int idx;
// 		idx = door_index_at(data, (int)new_pos.x, (int)new_pos.y);
// 		if (idx >= 0 && data->tab_doors && data->tab_doors[idx].lock)
// 		{
// 			if (open_door(data, idx) == 1)
// 			{
// 				data->player_pos = new_pos;
// 				mlx_clear_window(data->mlx_ptr, data->win_ptr);
// 				update_minimap(data);
// 			}
// 			return (0);
// 		}
// 	}
// 	if (data->map[(int)new_pos.y][(int)new_pos.x] != '1'
// 		&& !(data->map[(int)new_pos.y][(int)new_pos.x] == 'D'
// 		&& door_is_locked_at(data, new_pos.x, new_pos.y)))
// 	{
// 		data->player_pos = new_pos;
// 		mlx_clear_window(data->mlx_ptr, data->win_ptr);
// 		update_minimap(data);
// 	}
// 	return (0);
// }
