/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillichien <chillichien@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:01:49 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/09 19:43:16 by chillichien      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	calc_sprite_draw_area(t_data *d)
{
	d->spritescreenx = (int)((SCRN_W / 2)
			* (1 + d->transfx / d->transfy));
	d->vmovescreen = (int)(d->vmove / d->transfy);
	d->spriteh = abs((int)(SCRN_H / d->transfy));
	d->drawstarty = -d->spriteh / 2 + SCRN_H / 2 + d->pitch + d->vmovescreen;
	if (d->drawstarty < 0)
		d->drawstarty = 0;
	d->drawendy = d->spriteh / 2 + SCRN_H / 2 + d->pitch + d->vmovescreen;
	if (d->drawendy >= SCRN_H)
		d->drawendy = SCRN_H - 1;
	d->spritewidth = abs((int)(SCRN_H / d->transfy));
	d->drawstartx = -d->spritewidth / 2 + d->spritescreenx;
	if (d->drawstartx < 0)
		d->drawstartx = 0;
	d->drawendx = d->spritewidth / 2 + d->spritescreenx;
	if (d->drawendx >= SCRN_W)
		d->drawendx = SCRN_W - 1;
}

void	put_sprite_pixels(t_data *d, int texx, int stripe, int tex_idx)
{
	int	y;

	y = 0;
	while (y < d->drawendy)
	{
		d->pos = (y - (d->pitch + d->vmovescreen)) * 256
			- SCRN_H * 128 + d->spriteh * 128;
		d->texy = (d->pos * d->tex[tex_idx].height) / d->spriteh / 256;
		if (d->texy < 0)
			d->texy = 0;
		if (d->texy >= d->tex[tex_idx].height)
			d->texy = d->tex[tex_idx].height - 1;
		d->color = d->tex[tex_idx].pixels[d->texy
			* d->tex[tex_idx].width + texx];
		if ((d->color & 0x00FFFFFF) != 0)
		{
			if (d->transfy < d->pixeldepth[y][stripe])
			{
				put_px(d, stripe, y, d->color | 0xFF000000);
				d->pixeldepth[y][stripe] = d->transfy;
			}
		}
		y++;
	}
}

void	drawing_sprites(t_data *d, int tex_idx)
{
	int	stripe;
	int	texx;

	stripe = d->drawstartx;
	while (stripe < d->drawendx)
	{
		texx = (int)(256 * (stripe - (-d->spritewidth / 2 + d->spritescreenx))
				* d->tex[tex_idx].width / d->spritewidth) / 256;
		if (texx < 0)
			texx = 0;
		if (texx >= d->tex[tex_idx].width)
			texx = d->tex[tex_idx].width - 1;
		if (d->transfy > 0 && stripe >= 0 && stripe < SCRN_W)
		{
			put_sprite_pixels(d, texx, stripe, tex_idx);
		}
		stripe++;
	}
}

static int	chose_tex(t_data *d)
{
	if (d->monster_time % 2 == 0)
		return (12);
	else
		return (15);
}

void	handle_sprites(t_data *d)
{
	int			i;
	t_monster	*m;
	int			tex_idx;

	i = 0;
	tex_idx = chose_tex(d);
	while (i < d->monster_count)
	{
		m = &d->tab_m[i];
		d->spritex = m->pos.x - d->player_pos.x;
		d->spritey = m->pos.y - d->player_pos.y;
		d->inv = 1.0 / (d->cam.x * d->direction.y - d->direction.x * d->cam.y);
		d->transfx = d->inv * (d->direction.y
				* d->spritex - d->direction.x * d->spritey);
		d->transfy = d->inv * (-d->cam.y * d->spritex + d->cam.x * d->spritey);
		if (d->transfy <= 0)
		{
			i++;
			continue ;
		}
		calc_sprite_draw_area(d);
		drawing_sprites(d, tex_idx);
		i++;
	}
}
