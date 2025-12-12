/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:01:49 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/12 14:31:18 by wivallee         ###   ########.fr       */
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

static void	spx_put_pixels(t_data *d, t_ray *r, t_spx *s)
{
	int	y;

	y = 0;
	while (y < d->drawendy)
	{
		d->pos = (y - (d->pitch + d->vmovescreen)) * 256
			- SCRN_H * 128 + d->spriteh * 128;
		r->texy = (d->pos * d->tex[s->tex_idx].height)
			/ d->spriteh / 256;
		if (r->texy < 0)
			r->texy = 0;
		if (r->texy >= d->tex[s->tex_idx].height)
			r->texy = d->tex[s->tex_idx].height - 1;
		d->color = d->tex[s->tex_idx].pixels[r->texy
			* d->tex[s->tex_idx].width + s->texx];
		if ((d->color & 0x00FFFFFF) != 0
			&& d->transfy < d->pixeldepth[y][s->stripe])
		{
			put_px(d, s->stripe, y, d->color | 0xFF000000);
			d->pixeldepth[y][s->stripe] = d->transfy;
		}
		y++;
	}
}

void	drawing_sprites(t_data *d, int tex_idx, t_ray *r)
{
	t_spx	s;

	s.tex_idx = tex_idx;
	s.stripe = d->drawstartx;
	while (s.stripe < d->drawendx)
	{
		s.texx = (int)(256 * (s.stripe
					- (-d->spritewidth / 2 + d->spritescreenx))
				* d->tex[tex_idx].width / d->spritewidth) / 256;
		if (s.texx < 0)
			s.texx = 0;
		if (s.texx >= d->tex[tex_idx].width)
			s.texx = d->tex[tex_idx].width - 1;
		if (d->transfy > 0
			&& s.stripe >= 0 && s.stripe < SCRN_W)
			spx_put_pixels(d, r, &s);
		s.stripe++;
	}
}

static int	chose_tex(t_data *d)
{
	if (d->monster_time % 2 == 0)
		return (12);
	else
		return (15);
}

void	handle_sprites(t_data *d, t_ray *r)
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
		drawing_sprites(d, tex_idx, r);
		i++;
	}
}
