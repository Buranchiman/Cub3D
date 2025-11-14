/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:53:01 by mlemerci          #+#    #+#             */
/*   Updated: 2025/11/14 16:38:18 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

// int	key_hook(int keycode, t_data *data)
// {
// 	t_point			new_pos;

// 	if (keycode == KEY_ESC)
// 		ft_clean_exit(data, 0, "See you soon👋");
// 	data->held_key = keycode;
// 	new_pos = data->player_pos;
// 	if ((keycode == KEY_W) || (keycode == KEY_UP))
// 		new_pos.y -= 1;
// 	else if ((keycode == KEY_S) || (keycode == KEY_DOWN))
// 		new_pos.y += 1;
// 	else if ((keycode == KEY_A) || (keycode == KEY_LEFT))
// 		new_pos.x -= 1;
// 	else if ((keycode == KEY_D) || (keycode == KEY_RIGHT))
// 		new_pos.x += 1;
// 	if (data->map-new_pos.x != '1' && new_pos.y != '1')
// 	{
// 		data->player_pos = new_pos;
// 		mlx_clear_window(data->mlx_ptr, data->win_ptr); //temporarily disabled
// 		update_minimap(data);
// 	}
// 	return (0);
// }
