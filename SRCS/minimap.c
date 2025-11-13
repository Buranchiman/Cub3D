/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:02:35 by manon             #+#    #+#             */
/*   Updated: 2025/11/12 20:49:14 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void fil_textures_tab(t_data *data)
{
	if (data->texture[0].path)
		free(data->texture[0].path);
	data->texture[0].path = ft_strdup(WALL_MINIMAP);
	if (data->texture[1].path)
		free(data->texture[1].path);
	data->texture[1].path = ft_strdup(GROUND_MINIMAP);
	if (data->texture[2].path)
		free(data->texture[2].path);
	data->texture[2].path = ft_strdup(PLAYER_MINIMAP);
	if (data->texture[3].path)
		free(data->texture[3].path);
	data->texture[3].path = ft_strdup(EAST);
	if (data->texture[4].path)
		free(data->texture[4].path);
	data->texture[4].path = ft_strdup(NORTH);
	if (data->texture[5].path)
		free(data->texture[5].path);
	data->texture[5].path = ft_strdup(SOUTH);
	if (data->texture[6].path)
		free(data->texture[6].path);
	data->texture[6].path = ft_strdup(WEST);
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
			(ft_tablen(data->map) * IMG_SIZE), "Minimap");
	if (!data->win_ptr)
		ft_clean_exit(data, 1, "Window creation failed\n");
	fil_textures_tab(data);
	int n = 8;
	while(i < NBR_TEXTURES)
	{
		//data->texture[i].ptr = mlx_xpm_file_to_image(data->mlx_ptr,
		//	data->texture[i].path, &data->texture[i].width, 
		//	&data->texture[i].height);
		data->texture[i].ptr = mlx_xpm_file_to_image(data->mlx_ptr,	data->texture[i].path, &n, &n);
		open(data->texture[i].path, O_RDONLY);
		if (!data->texture[i].ptr)
			ft_clean_exit(data, 1, "Failed to load minimap texture");
		i++;
	}

}

void	display_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	//int	tile_size = IMG_SIZE/8;
	//int offset_x = (ft_strlen(data->map[0]) * IMG_SIZE) - (ft_strlen(data->map[0]) * tile_size) - 20;
	//int offset_y = (ft_tablen(data->map) * IMG_SIZE) - (ft_tablen(data->map) * tile_size) - 20;  
	//printf ("tile_size: %d, offset_x: %d, offset_y: %d\n", tile_size, offset_x, offset_y);
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')	
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->texture[0].ptr, x * IMG_SIZE/8, y * IMG_SIZE/8);
			else if (data->map[y][x] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->texture[1].ptr, x * IMG_SIZE/8, y * IMG_SIZE/8);
			else if (ft_strchr("NSWE", data->map[y][x]))
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->texture[2].ptr, x * IMG_SIZE/8, y * IMG_SIZE/8);
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
