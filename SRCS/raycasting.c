/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:10:34 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/05 18:46:38 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

// void		calc_gate_area(t_data *d, t_tex *gatetex,
// 	int x, double dist, int gi)
// {
// 	d->lineheight = (int)(SCRN_H / dist);
// 	d->drawstart = -d->lineheight / 2 + SCRN_H / 2 + d->pitch;
// 	if (d->drawstart < 0)
// 		d->drawstart = 0;
// 	d->drawend = d->lineheight / 2 + SCRN_H / 2 + d->pitch;
// 	if (d->drawend >= SCRN_H)
// 		d->drawend = SCRN_H - 1;
// 	d->texx = d->gateLayers[x][gi].texX;
// 	d->step = 1.0 * gatetex->height / d->lineheight;
// 	d->texpos = (d->drawstart - d->pitch - SCRN_H
// 			/ 2 + d->lineheight / 2) * d->step;
// }

// void		draw_gates(t_data *d, t_tex *gatetex, int x, double dist)
// {
// 	int	y;

// 	y = d->drawstart;
// 	while (y < d->drawend)
// 	{
// 		d->texy = (int)d->texpos;
// 		d->texpos += d->step;
// 		if (d->texy < 0)
// 			d->texy = 0;
// 		if (d->texy >= gatetex->height)
// 			d->texy = gatetex->height - 1;
// 		d->color = gatetex->pixels[d->texy * gatetex->width + d->texx];
// 		// Treat pure black (RGB = 0) as transparent
// 		if ((d->color & 0x00FFFFFF) != 0) // not transparent
// 		{
// 			// GATE SHOULD ONLY DRAW IF IT IS CLOSER THAN THE SPRITE
// 			if (dist < d->pixelDepth[y][x])
// 			{
// 				put_px(d, x, y, d->color | 0xFF000000);
// 				d->pixelDepth[y][x] = dist;
// 			}
// 		}
// 		y++;
// 	}
// }
// void	door_back_to_front(t_data  *d, int x, int count)
// {
// 	t_tex	*gatetex;
// 	int		gi;
// 	double	dist;

// 	gi = count;
// 	while (gi >= 0)
// 	{
// 		dist = d->gateLayers[x][gi].dist;
// 		if (dist <= 0.0)
// 		{
// 			gi--;
// 			continue ;
// 		}
// 		gatetex = &d->tex[d->gateLayers[x][gi].locked];
// 		calc_gate_area(d, gatetex, x, dist, gi);
// 		draw_gates(d, gatetex, x, dist);
// 		gi--;
// 	}
// }

// static void	handle_gates(t_data *d)
// {
// 	int		x;
// 	int		count;

// 	x = 0;
// 	while (x < SCRN_W)
// 	{
// 		count = d->gateCount[x];
// 		if (count <= 0)
// 		{
// 			x++;
// 			continue ;
// 		}
// 		// draw from far → near so closer gate overwrites farther
// 		door_back_to_front(d, x, count);
// 		x++;
// 	}
// }

void	first_calc(t_data *d, int x)
{
	double	camx;

	camx = 2 * x / (double)SCRN_W - 1;
	d->raydirx = d->direction.x + d->cam.x * camx;
	d->raydiry = d->direction.y + d->cam.y * camx;
	d->mapx = (int)d->player_pos.x;
	d->mapy = (int)d->player_pos.y;
	if (d->raydirx == 0)
		d->deltadistx = 1e30;
	else
		d->deltadistx = fabs(1 / d->raydirx);
	if (d->raydiry == 0)
		d->deltadisty = 1e30;
	else
		d->deltadisty = fabs(1 / d->raydiry);
}

void	step_calc(t_data *d)
{
	if (d->raydirx < 0)
	{
		d->stepx = -1;
		d->sidedistx = (d->player_pos.x - d->mapx) * d->deltadistx;
	}
	else
	{
		d->stepx = 1;
		d->sidedistx = (d->mapx + 1.0 - d->player_pos.x) * d->deltadistx;
	}
	if (d->raydiry < 0)
	{
		d->stepy = -1;
		d->sidedisty = (d->player_pos.y - d->mapy) * d->deltadisty;
	}
	else
	{
		d->stepy = 1;
		d->sidedisty = (d->mapy + 1.0 - d->player_pos.y) * d->deltadisty;
	}
}

void	get_wallside(t_data *d)
{
//jump to next map square, either in x-direction, or in y-direction
	if (d->sidedistx < d->sidedisty)
	{
		d->sidedistx += d->deltadistx;
		d->mapx += d->stepx;
		d->side = 0;
		if (d->stepx == 1)
			d->cardinal = CARDEAST;
		else
			d->cardinal = CARDWEST;
	}
	else
	{
		d->sidedisty += d->deltadisty;
		d->mapy += d->stepy;
		d->side = 1;
		if (d->stepy == 1)
			d->cardinal = CARDNORTH;
		else
			d->cardinal = CARDSOUTH;
	}
}

void	hit_wall(t_data *d, int x)
{
	int		gate_tex;
	double	wallx;
	double	gatedist;
	int		texx_gate;

	if (door_is_locked_at(d, d->mapx, d->mapy))
		gate_tex = 11;
	else
		gate_tex = 12;
	// distance to this gate
	if (d->side == 0)
		gatedist = d->sidedistx - d->deltadistx;
	else
		gatedist = d->sidedisty - d->deltadisty;
	// compute where on the tex we d->hit (like walls)
	if (d->side == 0)
		wallx = d->player_pos.y + gatedist * d->raydiry;
	else
		wallx = d->player_pos.x + gatedist * d->raydirx;
	wallx -= floor(wallx);
	texx_gate = (int)(wallx * (double)d->tex[gate_tex].width);
	if (texx_gate < 0) texx_gate = 0;
	if (texx_gate >= d->tex[gate_tex].width)
		texx_gate = d->tex[gate_tex].width - 1;
	// store this gate layer for this column
	assign_gate_value(x, gate_tex, gatedist, texx_gate);
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

void	calc_draw_area(t_data *d)
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
		calc_draw_area(d);
		// draw each vertical stripe of the sprite
		drawing_sprites(d);
		i++;
	}
}

void	calc_wall_drawing_area(t_data *d)
{
	if (d->side == 0)
		d->perpwalldist = (d->sidedistx - d->deltadistx);
	else
		d->perpwalldist = (d->sidedisty - d->deltadisty);
	 //Calculate height of line to draw on screen
	if (d->perpwalldist < 1e-6)
		d->perpwalldist = 1e-6;
	d->lineheight = (int)(SCRN_H / d->perpwalldist);
	//calculate lowest and highest pixel to fill in current stripe
	d->drawstart = -d->lineheight / 2 + SCRN_H / 2 + d->pitch;
	if (d->drawstart < 0)
		d->drawstart = 0;
	d->drawend = d->lineheight / 2 + SCRN_H / 2 + d->pitch;
	if (d->drawend >= SCRN_H)
		d->drawend = SCRN_H - 1;
}

void	draw_walls(t_data *d, int x)
{
	int	y;

	y = 0;
	y = d->drawstart;
	while (y < d->drawend)
	{
		// Cast the tex coordinate to integer, and mask with (TEXHEIGHT - 1) in case of overflow
		d->texy = (int)d->texpos & (d->tex[d->cardinal].height - 1);
		d->texpos += d->step;
		d->color = d->tex[d->cardinal].pixels[d->texy
			* d->tex[d->cardinal].width + d->texx];
		// unsigned int d->color = 0xFF0000FF;
		//make d->color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// if(d->side == 1) d->color = (d->color >> 1) & 8355711;
		put_px(d, x, y, d->color | 0xFF000000);
		d->pixelDepth[y][x] = d->perpwalldist;   // wall is at this distance
		y++;
	}
	while (y < SCRN_H)
	{
		put_px(d, x, y, FLOOR_COLOR);
		y++;
	}
}

void	draw_ceiling(t_data *d, int x)
{
	int	y;

	y = 0;
	while (y < d->drawstart)
	{
		if (d->sky.pixels && d->sky.width > 0 && d->sky.height > 0)
		{
			d->texx = (int)((double)x * d->sky.width / (double)SCRN_W);
			d->texy = (int)((double)y * d->sky.height / (double)SCRN_H);
			d->color = d->sky.pixels[d->texy * d->sky.width + d->texx];
			put_px(d, x, y, d->color | 0xFF000000);
		}
		else
			put_px(d, x, y, CEILING_COLOR);
		y++;
	}
}

void	walls_final_cal(t_data *d, double wallx)
{
	 //x coordinate on the tex
	d->texx = (int)(wallx * (double)d->tex[d->cardinal].width);
	if (d->side == 0 && d->raydirx > 0)
		d->texx = d->tex[d->cardinal].width - d->texx - 1;
	if (d->side == 1 && d->raydiry < 0)
		d->texx = d->tex[d->cardinal].width - d->texx - 1;
	 // TODO: an integer-only bresenham or DDA like algorithm could make the tex coordinate stepping faster
	// How much to increase the tex coordinate per screen pixel
	d->step = 1.0 * d->tex[d->cardinal].height / d->lineheight;
	// Starting tex coordinate
	d->texpos = (d->drawstart - d->pitch - SCRN_H / 2 + d->lineheight / 2) * d->step;
}

void	perform_dda(t_data *d, int x)
{
	while (d->hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		get_wallside(d);
		//Check if ray has d->hit a wall
		if (d->map[d->mapy][d->mapx] == 'D') // transparent gate d->map[d->mapy][d->mapx]
		{
			hit_wall(d, x);
			// DO NOT mark d->hit, this gate is not a blocking wall
			continue;
		}
		else if (d->map[d->mapy][d->mapx] == '1')
		{
			// solid wall or door: stop ray here
			d->cardinal = fetch_tex(d->mapx, d->mapy);
			d->hit = 1;
		}
	}
}

void	reset_gates(t_data *d)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < SCRN_W)
	{
		d->gateCount[i] = 0;
		i++;
	}
	y = 0;
	while (y < SCRN_H)
	{
		x = 0;
		while (x < SCRN_W)
		{
			d->pixelDepth[y][x] = 1e30;
			x++;
		}
		y++;
	}
}

int	raycasting(t_data *d)
{
	int		x;
	double	wallx; //where exactly the wall was d->hit

	x = 0;
	// reset gate counts for this frame
	reset_gates(d);
	while (x < SCRN_W)
	{
		first_calc(d, x);
		 //calculate d->step and initial sideDist
		//perform DDA
		d->hit = 0;
		step_calc(d);
		perform_dda(d, x);
		calc_wall_drawing_area(d);
		draw_ceiling(d, x);
		 //calculate value of wallx
		if (d->side == 0)
			wallx = d->player_pos.y + d->perpwalldist * d->raydiry;
		else
			wallx = d->player_pos.x + d->perpwalldist * d->raydirx;
		wallx -= floor((wallx));
		 //x coordinate on the tex
		walls_final_cal(d, wallx);
		draw_walls(d, x);
		x++;
	}
	handle_sprites(d);
	handle_gates(d);
	return (0);
}

void	mouse_rotation(t_data *d)
{
	int		dx;
	double	rot;
	double	c;
	double	s;
	double	old_dir;

	dx = d->mouse_dx;
	d->mouse_dx = 0;
	rot = dx * d->mouse_sens;
	if (rot > d->max_rot_frame)
		rot = d->max_rot_frame;
	if (rot < -d->max_rot_frame)
	rot = -d->max_rot_frame;
	if (rot != 0.0)
	{
		c = cos(rot);
		s = sin(rot);
		old_dir = d->direction.x;
		d->direction.x = d->direction.x * c - d->direction.y * s;
		d->direction.y = old_dir * s + d->direction.y * c;
		d->cam.y = d->cam.x * s + d->cam.y * c;
		d->cam.x = d->cam.x * c - d->cam.y * s;
	}
}

// compose minimap into the main image buffer, then blit once
int	render_frame(void *param)
{
	t_data			*d;
	double			now;
	unsigned long	now_ms;

	(void)param;
	d = get_data();
	now = get_time();
	d->deltatime = now - d->lasttime;
	d->lasttime = now;
	now_ms = (unsigned long)(now * 1000.0);
	if (now_ms - d->last_update >= 120UL)
	{
		monsters_move(d);
		d->last_update = now_ms;
	}
	if (d->deltatime > 0.05)
		d->deltatime = 0.05;
	mouse_rotation(d);
	update_player(d);
	raycasting(d);
	display_minimap(d, 0, 0);
	mlx_put_image_to_window(d->mlx_ptr,
		d->win_ptr, d->mlx_img->img, 0, 0);
	return (0);
}
