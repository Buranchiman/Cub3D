#include "../INCLUDE/cube.h"

void	calc_sprite_draw_area(t_data *d)
{
	// screen X
	d->spritescreenx = (int)((SCRN_W / 2) * (1 + d->transformx / d->transformy));
	// world-space vertical offset (feet height, tune 0.0–0.7)
	d->vmovescreen = (int)(d->vmove / d->transformy);   // <-- NO + d->pitch here
	// sprite dimensions (scale with distance)
	d->spriteh = abs((int)(SCRN_H / d->transformy));
	d->drawstarty = -d->spriteh / 2 + SCRN_H / 2 + d->pitch + d->vmovescreen;
	if (d->drawstarty < 0)
		d->drawstarty = 0;
	d->drawendy = d->spriteh / 2 + SCRN_H / 2 + d->pitch + d->vmovescreen;
	if (d->drawendy >= SCRN_H)
		d->drawendy = SCRN_H - 1;
	d->spritewidth = abs((int)(SCRN_H / d->transformy));
	d->drawstartx = -d->spritewidth / 2 + d->spritescreenx;
	if (d->drawstartx < 0)
		d->drawstartx = 0;
	d->drawendx = d->spritewidth / 2 + d->spritescreenx;
	if (d->drawendx >= SCRN_W)
		d->drawendx = SCRN_W - 1;
}

void	put_sprite_pixels(t_data *d, int texx, int stripe)
{
	int	y;

	y = 0;
	while (y < d->drawendy)
	{
		d->pos = (y - (d->pitch + d->vmovescreen)) * 256
			- SCRN_H * 128 + d->spriteh * 128;
		d->texy = (d->pos * d->tex[10].height) / d->spriteh / 256;
		if (d->texy < 0)
			d->texy = 0;
		if (d->texy >= d->tex[10].height)
			d->texy = d->tex[10].height - 1;
		d->color = d->tex[10].pixels[d->texy * d->tex[10].width + texx];
		if ((d->color & 0x00FFFFFF) != 0) // non-transparent pixel
		{
			// Only draw if sprite is in front of whatever is already there
			if (d->transformy < d->pixelDepth[y][stripe])
			{
				put_px(d, stripe, y, d->color | 0xFF000000);
				d->pixelDepth[y][stripe] = d->transformy;
			}
		}
		y++;
	// if sprite pixel is transparent: do nothing, don't change pixelDepth
	}
}

void	drawing_sprites(t_data *d)
{
	int	stripe;
	int	texx;

	stripe = d->drawstartx;
	while (stripe < d->drawendx)
	{
		texx = (int)(256 * (stripe - (-d->spritewidth / 2 + d->spritescreenx))
				* d->tex[10].width / d->spritewidth) / 256;
		if (texx < 0)
			texx = 0;
		if (texx >= d->tex[10].width)
			texx = d->tex[10].width - 1;
		if (d->transformy > 0 && stripe >= 0 && stripe < SCRN_W)
		{
			put_sprite_pixels(d, texx, stripe);
			// if sprite pixel is transparent: do nothing, don't change pixelDepth
		}
		stripe++;
	}
}

void	handle_sprites(t_data *d)
{
	int			i;
	t_monster	*m;

	i = 0;
	while (i < d->monster_count)
	{
		m = &d->tab_m[i];
		// relative to player
		d->spritex = m->pos.x - d->player_pos.x;
		d->spritey = m->pos.y - d->player_pos.y;
		// inverse determinant of cam matrix
		d->invdet = 1.0 / (d->cam.x * d->direction.y
				- d->direction.x * d->cam.y);
		// transform to cam space
		d->transformx = d->invdet * (d->direction.y * d->spritex - d->direction.x * d->spritey);
		d->transformy = d->invdet * (-d->cam.y * d->spritex + d->cam.x * d->spritey);
		if (d->transformy <= 0)
		{
			i++;
			continue ;
		}
		calc_sprite_draw_area(d);
		// draw each vertical stripe of the sprite
		drawing_sprites(d);
		i++;
	}
}
