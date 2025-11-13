/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:02:35 by manon             #+#    #+#             */
/*   Updated: 2025/11/13 16:38:20 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void fil_textures_tab(t_data *data)
{
	data->texture[0].path = WALL_MINIMAP;
	data->texture[1].path = GROUND_MINIMAP;
	data->texture[2].path = PLAYER_MINIMAP;
}

void	display_window(t_data *data)
{
    int i;

    i = 0;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_clean_exit(data, 1, "MLX init failed\n");
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			(ft_strlen(data->map[0]) * IMG_SIZE),
			(ft_tablen(data->map) * IMG_SIZE),
			"Minimap");
	if (!data->win_ptr)
		ft_clean_exit(data, 1, "Window creation failed\n");
	fil_textures_tab(data);
	while(i < 3)
	{
		//printf("path: %s width: %d height: %d", data->texture[i].path, data->texture[i].width, data->texture[i].height);
		//data->texture[i].ptr = mlx_xpm_file_to_image(data->mlx_ptr,
		//	data->texture[i].path, &data->texture[i].width,
		//	&data->texture[i].height);
		int j = 32;
		data->texture[i].ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			data->texture[i].path, &j, &j);
		if (!data->texture[i].ptr)
			ft_clean_exit(data, 1, "Failed to load minimap texture\n");
		i++;
	}

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
			//else
			//	;
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
