/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:02:35 by manon             #+#    #+#             */
/*   Updated: 2025/11/21 21:56:09 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	fil_textures_tab(t_data *data)
{
	if (data->texture[0].path)
		free(data->texture[0].path);
	data->texture[0].path = ft_strdup(NORTH);
	if (data->texture[1].path)
		free(data->texture[1].path);
	data->texture[1].path = ft_strdup(SOUTH);
	if (data->texture[2].path)
		free(data->texture[2].path);
	data->texture[2].path = ft_strdup(WEST);
	if (data->texture[3].path)
		free(data->texture[3].path);
	data->texture[3].path = ft_strdup(EAST);
	if (data->texture[4].path)
		free(data->texture[4].path);
	data->texture[4].path = ft_strdup(PLAYER_MINIMAP);
	if (data->texture[5].path)
		free(data->texture[5].path);
	data->texture[5].path = ft_strdup(GROUND_MINIMAP);
	if (data->texture[6].path)
		free(data->texture[6].path);
	data->texture[6].path = ft_strdup(WALL_MINIMAP);
	data->texture[7].path = ft_strdup(MONSTER);
	data->texture[8].path = ft_strdup(DOOR_CLOSED);
	data->texture[9].path = ft_strdup(DOOR_OPEN);
}

int	init_pixels(t_texture *tex)
{
	int	bytes_per_pixel;

	bytes_per_pixel = tex->ptr->bpp / 8;
	tex->pixels = malloc(tex->width * tex->height * sizeof(uint32_t));
	if (!tex->pixels)
		return (1);
	int y = 0;
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

void	display_window(t_data *data)
{
	int i;

	i = 0;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_clean_exit(data, 1, "MLX init failed\n");
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREENWIDTH, SCREENHEIGHT, "Minimap");
	if (!data->win_ptr)
		ft_clean_exit(data, 1, "Window creation failed\n");
	fil_textures_tab(data);
	while(i < NBR_TEXTURES)
	{
		data->texture[i].ptr = init_img();
		data->texture[i].ptr->img = mlx_xpm_file_to_image(data->mlx_ptr, data->texture[i].path, &data->texture[i].width, &data->texture[i].height);
		if (!data->texture[i].ptr->img)
			ft_clean_exit(data, 1, "Failed to load minimap texture");
		data->texture[i].ptr->addr = mlx_get_data_addr(data->texture[i].ptr->img, &data->texture[i].ptr->bpp, &data->texture[i].ptr->line_len, &data->texture[i].ptr->endian);
		init_pixels(&data->texture[i]);
		i++;
	}
	if (data->sky_fallback_path)
	{
		data->sky_texture.path = ft_strdup(data->sky_fallback_path);
		data->sky_texture.ptr = init_img();
		data->sky_texture.ptr->img = mlx_xpm_file_to_image(data->mlx_ptr, data->sky_texture.path, &data->sky_texture.width, &data->sky_texture.height);
		if (data->sky_texture.ptr->img)
		{
			data->sky_texture.ptr->addr = mlx_get_data_addr(data->sky_texture.ptr->img, &data->sky_texture.ptr->bpp, &data->sky_texture.ptr->line_len, &data->sky_texture.ptr->endian);
			if (init_pixels(&data->sky_texture))
				ft_printf(2, "[warning] failed to init sky texture pixels\n");
		}
		else
		{
			ft_printf(2, "[warning] unable to load sky fallback '%s'\n", data->sky_fallback_path);
			free(data->sky_texture.path);
			data->sky_texture.path = NULL;
		}
	}
}

static inline void	put_pixel_img(t_data *d, int x, int y, unsigned int color)
{
	if (!d || !d->mlx_img || !d->mlx_img->addr)
		return;
	if ((unsigned)x >= (unsigned)SCREENWIDTH || (unsigned)y >= (unsigned)SCREENHEIGHT)
		return;
	char *p = d->mlx_img->addr + y * d->mlx_img->line_len + x * (d->mlx_img->bpp / 8);
	*(unsigned int *)p = color;
}

static void	draw_tex_on_img(t_data *d, t_texture *tex, int px, int py, int size)
{
	if (!d || !tex || !tex->pixels)
		return;
	int sy = 0;
	while (sy < size)
	{
		int sx = 0;
		while (sx < size)
		{
			int tx = (sx * tex->width) / size;
			int ty = (sy * tex->height) / size;
			unsigned int color = tex->pixels[ty * tex->width + tx];
			if (color == 0xFF000000)
			{
				sx++;
				continue;
			}
			put_pixel_img(d, px + sx, py + sy, color);
			sx++;
		}
		sy++;
	}
}

void	display_minimap(t_data *data)
{
	int x, y;
	const int size = IMG_SIZE / 8;

	if (!data || !data->mlx_img || !data->mlx_img->addr)
		return;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			int screen_x = 1604 + x * size;
			int screen_y = 764 + y * size;
			int tex_idx = 5;
			if (data->map[y][x] == '1')
				tex_idx = 6;
			else if (ft_strchr("NSWE", data->map[y][x]))
				tex_idx = 5;
			else if (data->map[y][x] == 'D')
			{
				int idx = door_index_at(data, x, y);
				if (idx >= 0 && data->tab_doors && data->tab_doors[idx].lock)
					tex_idx = 8;
				else
					tex_idx = 9;
			}
			draw_tex_on_img(data, &data->texture[tex_idx], screen_x, screen_y, size);
			if (data->tab_monsters)
			{
				int i = 0;
				while (i < data->tab_monsters[0].count)
				{
					if ((int)data->tab_monsters[i].pos.x == x && (int)data->tab_monsters[i].pos.y == y)
						draw_tex_on_img(data, &data->texture[7], screen_x, screen_y, size);
					i++;
				}
			}
			if (y == (int)data->player_pos.y && x == (int)data->player_pos.x)
				draw_tex_on_img(data, &data->texture[4], screen_x, screen_y, size);
			x++;
		}
		y++;
	}
}
