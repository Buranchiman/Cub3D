/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:00:00 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/02 15:02:42 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

static void	init_sprite_screen(t_data *d, t_monster *m, int *sx,
		double *tr_x_y)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = m->pos.x - d->player_pos.x;
	sprite_y = m->pos.y - d->player_pos.y;
	inv_det = 1.0 / (d->cam.x * d->direction.y - d->direction.x * d->cam.y);
	tr_x_y[0] = inv_det * (d->direction.y * sprite_x
			- d->direction.x * sprite_y);
	tr_x_y[1] = inv_det * (-d->cam.y * sprite_x + d->cam.x * sprite_y);
	if (tr_x_y[1] <= 0.0)
	{
		*sx = -1;
		return ;
	}
	*sx = (int)((SCREENWIDTH / 2)
			* (1.0 + tr_x_y[0] / tr_x_y[1]));
}

static void	compute_sprite_bounds(double tr_y, int pitch,
		int *bounds)
{
	int	sprite_h;
	int	sprite_w;
	int	draw_start_y;
	int	draw_end_y;
	int	draw_start_x;
	int	draw_end_x;

	sprite_h = (int)fabs((double)SCREENHEIGHT / tr_y);
	sprite_w = (int)fabs((double)SCREENHEIGHT / tr_y);
	draw_start_y = -sprite_h / 2 + SCREENHEIGHT / 2 + pitch;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_h / 2 + SCREENHEIGHT / 2 + pitch;
	if (draw_end_y >= SCREENHEIGHT)
		draw_end_y = SCREENHEIGHT - 1;
	draw_start_x = -sprite_w / 2 + bounds[0];
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_w / 2 + bounds[0];
	if (draw_end_x >= SCREENWIDTH)
		draw_end_x = SCREENWIDTH - 1;
	bounds[1] = draw_start_y;
	bounds[2] = draw_end_y;
	bounds[3] = draw_start_x;
	bounds[4] = draw_end_x;
	bounds[5] = sprite_h;
	bounds[6] = sprite_w;
}

static void	draw_sprite_stripe(t_data *d, int stripe, int *b, double tr_y)
{
	int				tex_x;
	int				y;
	int				dv;
	int				tex_y;
	unsigned int	color;

	tex_x = (int)(256 * (stripe - (-b[6] / 2 + b[0]))
			* d->texture[10].width / b[6]) / 256;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= d->texture[10].width)
		tex_x = d->texture[10].width - 1;
	if (!(tr_y > 0.0 && stripe >= 0 && stripe < SCREENWIDTH))
		return ;
	y = b[1];
	while (y < b[2])
	{
		dv = (y - b[7]) * 256 - SCREENHEIGHT * 128 + b[5] * 128;
		tex_y = (dv * d->texture[10].height) / b[5] / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= d->texture[10].height)
			tex_y = d->texture[10].height - 1;
		color = d->texture[10].pixels[tex_y
			* d->texture[10].width + tex_x];
		if ((color & 0x00FFFFFF) != 0
			&& tr_y < d->pixelDepth[y][stripe])
		{
			put_px(d, stripe, y, color | 0xFF000000);
			d->pixelDepth[y][stripe] = tr_y;
		}
		y++;
	}
}

void	draw_sprites(t_data *d, int pitch)
{
	int			i;
	t_monster	*m;
	int			sprite_x;
	double		tr_x_y[2];
	int			bounds[8];
	int			stripe;

	i = 0;
	while (i < d->monster_count)
	{
		m = &d->tab_monsters[i];
		sprite_x = 0;
		init_sprite_screen(d, m, &sprite_x, tr_x_y);
		if (sprite_x >= 0)
		{
			bounds[0] = sprite_x;
			compute_sprite_bounds(tr_x_y[1], pitch, bounds);
			bounds[7] = pitch + (int)(0.3 / tr_x_y[1]);
			stripe = bounds[3];
			while (stripe < bounds[4])
			{
				draw_sprite_stripe(d, stripe, bounds, tr_x_y[1]);
				stripe++;
			}
		}
		i++;
	}
}
