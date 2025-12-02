/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 02:21:55 by manon             #+#    #+#             */
/*   Updated: 2025/12/02 16:04:46 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	fil_texs_tab(t_data *data)
{
	int	i;

	i = 0;
	data->tex[0].path = ft_strdup(NORTH);
	data->tex[1].path = ft_strdup(SOUTH);
	data->tex[2].path = ft_strdup(WEST);
	data->tex[3].path = ft_strdup(EAST);
	data->tex[4].path = ft_strdup(PLAYER_MINIMAP);
	data->tex[5].path = ft_strdup(GROUND_MINIMAP);
	data->tex[6].path = ft_strdup(WALL_MINIMAP);
	data->tex[7].path = ft_strdup(MONSTER_MAP);
	data->tex[8].path = ft_strdup(DOOR_CLOSED_MAP);
	data->tex[9].path = ft_strdup(DOOR_OPENED_MAP);
	data->tex[10].path = ft_strdup(MONSTER);
	data->tex[11].path = ft_strdup(DOOR_CLOSED);
	data->tex[12].path = ft_strdup(DOOR_OPENED);
	data->tex[13].path = ft_strdup(MONSTER2);
	while (i < NBR_TEXTURES)
	{
		if (!data->tex[i].path)
			ft_clean_exit(data, 1, "Failed to allocate tex path");
		i++;
	}
}

int	init_pixels(t_tex *tex)
{
	int	bytes_per_pixel;
	int	y;

	bytes_per_pixel = tex->ptr->bpp / 8;
	tex->pixels = malloc(tex->width * tex->height * sizeof(uint32_t));
	if (!tex->pixels)
		return (1);
	y = 0;
	while (y < tex->height)
	{
		memcpy(
			tex->pixels + y * tex->width,
			tex->ptr->addr + y * tex->ptr->line_len,
			tex->width * bytes_per_pixel
			);
		y++;
	}
	return (0);
}

void	display_sky(t_data *data)
{
	data->sky.path = ft_strdup(data->sky_path);
	data->sky.ptr = init_img();
	data->sky.ptr->img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->sky.path, &data->sky.width, &data->sky.height);
	if (data->sky.ptr->img)
	{
		data->sky.ptr->addr = mlx_get_data_addr(data->sky.ptr->img,
				&data->sky.ptr->bpp, &data->sky.ptr->line_len,
				&data->sky.ptr->endian);
		if (init_pixels(&data->sky))
			ft_printf(1, "failed to init sky tex pixels");
	}
	else
	{
		ft_printf(1, "unable to load sky fallback '%s'", data->sky_path);
		free(data->sky.path);
		data->sky.path = NULL;
	}
}

void	display_window(t_data *data, int i)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_clean_exit(data, 1, "mlx init failed\n");
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCRN_W, SCRN_H,
			"Where are the escape ?");
	if (!data->win_ptr)
		ft_clean_exit(data, 1, "Window creation failed\n");
	fil_texs_tab(data);
	while (i < NBR_TEXTURES)
	{
		data->tex[i].ptr = init_img();
		data->tex[i].ptr->img = mlx_xpm_file_to_image(data->mlx_ptr,
				data->tex[i].path, &data->tex[i].width, &data->tex[i].height);
		if (!data->tex[i].ptr->img)
			ft_clean_exit(data, 1, "Failed to load tex");
		data->tex[i].ptr->addr = mlx_get_data_addr(data->tex[i].ptr->img,
				&data->tex[i].ptr->bpp, &data->tex[i].ptr->line_len,
				&data->tex[i].ptr->endian);
		init_pixels(&data->tex[i]);
		i++;
	}
	if (data->sky_path)
		display_sky(data);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, SCRN_W / 2, SCRN_H / 2);
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
}
