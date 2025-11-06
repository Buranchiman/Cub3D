/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:52:52 by manon             #+#    #+#             */
/*   Updated: 2025/11/05 19:06:06 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../INCLUDE/cube.h"

void	draw(t_data *data, int x, int y)
{
	if (y == 0)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->texture[0].ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (y == 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->texture[1].ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (x == 0)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->texture[2].ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (x == 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->texture[3].ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (x == 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->texture[4].ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (x == 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->texture[5].ptr, x * IMG_SIZE, y * IMG_SIZE);
}

void	render_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->data[y])
	{
		x = 0;
		while (data->map->data[y][x])
		{
			draw_(data, x, y);
			x++;
		}
		y++;
	}
	display_moves(data);
}

void	quit_and_free(t_data *data)
{
	//system("pkill mpg123"); ->si ajout de musique
	//system("stty sane");
	int i = 0;
	while(data->texture[i])
	{
		if (data->texture[i].ptr)
			mlx_destroy_image(data->mlx_ptr, data->texture[i].ptr);
		i++;
	}
	if (data->mlx_ptr && data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(0);
}
