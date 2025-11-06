/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:02:35 by manon             #+#    #+#             */
/*   Updated: 2025/11/06 16:07:14 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	display_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_clean_exit(data, 1, "MLX init failed\n");
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			(ft_tablen(data->map) * IMG_SIZE),
			(ft_strlen(data->map[0]) * IMG_SIZE), "Minimap");
	if (!data->win_ptr)
		ft_clean_exit(data, 1, "Window creation failed\n");
}

void	display_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')	
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->texture[0].ptr, x * IMG_SIZE, y * IMG_SIZE);
			else if (data->map[y][x] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->texture[1].ptr, x * IMG_SIZE, y * IMG_SIZE);
			else if (data->map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->texture[2].ptr, x * IMG_SIZE, y * IMG_SIZE);
			x++;
		}
		y++;
	}
}

void	update_minimap(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	display_minimap(data);
}
