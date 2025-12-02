/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:02:35 by manon             #+#    #+#             */
/*   Updated: 2025/12/01 02:30:23 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

static inline void	put_pixel_img(t_data *d, int x, int y, unsigned int color)
{
	char	*p;

	if (!d || !d->mlx_img || !d->mlx_img->addr)
		return ;
	if ((unsigned)x >= (unsigned)SCRN_W || (unsigned)y >= (unsigned)SCRN_H)
		return ;
	p = d->mlx_img->addr + y * d->mlx_img->line_len + x * (d->mlx_img->bpp / 8);
	*(unsigned int *)p = color;
}

static void	draw_tex_on_img(t_data *d, t_texture *tex, int px, int py)
{
	int				sy;
	int				sx;
	int				tx;
	int				ty;
	unsigned int	color;

	sy = 0;
	while (sy < 8)
	{
		sx = 0;
		while (sx < 8)
		{
			tx = (sx * tex->width) / 8;
			ty = (sy * tex->height) / 8;
			color = tex->pixels[ty * tex->width + tx];
			if (color == 0xFF000000)
			{
				sx++;
				continue ;
			}
			put_pixel_img(d, px + sx, py + sy, color);
			sx++;
		}
		sy++;
	}
}

void	display_other(t_data *data, int y, int x, int tex_idx)
{
	int	i;
	int	screen_x;
	int	screen_y;

	screen_x = 1604 + x * 8;
	screen_y = 764 + y * 8;
	if (data->map[y][x] == '1')
		tex_idx = 6;
	draw_tex_on_img(data, &data->tex[tex_idx], screen_x, screen_y);
	if (data->tab_m)
	{
		i = 0;
		while (i < data->monster_count)
		{
			if ((int)data->tab_m[i].pos.x == x
				&& (int)data->tab_m[i].pos.y == y)
				draw_tex_on_img(data, &data->tex[7], screen_x, screen_y);
			i++;
		}
	}
	if (y == (int)data->player_pos.y && x == (int)data->player_pos.x)
		draw_tex_on_img(data, &data->tex[4], screen_x, screen_y);
}

void	display_minimap(t_data *data, int x, int y)
{
	int	tex_idx;
	int	idx;

	if (!data || !data->mlx_img || !data->mlx_img->addr)
		return ;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			tex_idx = 5;
			if (data->map[y][x] == 'D')
			{
				idx = door_index_at(data, x, y);
				if (idx >= 0 && data->tab_doors && data->tab_doors[idx].lock)
					tex_idx = 8;
				else
					tex_idx = 9;
			}
			display_other(data, y, x, tex_idx);
			x++;
		}
		y++;
	}
}
