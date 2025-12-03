/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:10:34 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/03 16:17:40 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

static inline void	put_px(t_data *d, int x, int y, unsigned int argb)
{
	char	*p;

	if ((unsigned)x >= (unsigned)SCRN_W
		|| (unsigned)y >= (unsigned)SCRN_H)
		return ;
	p = d->mlx_img->addr + y * d->mlx_img->line_len + x * (d->mlx_img->bpp / 8);
	*(unsigned int *)p = argb;
}

static int	fetch_tex(int x, int y)
{
	t_data	*d;
	int		idx;

	d = get_data();
	if (d->map[d->mapy][d->mapx] == 'D')
	{
		idx = door_index_at(d, x, y);
		if (idx >= 0 && d->tab_doors && d->tab_doors[idx].lock)
			return (11);
		else if (idx >= 0 && d->tab_doors && !d->tab_doors[idx].lock)
			return (12);
	}
	return (d->cardinal);
}

void	rotate_player(t_data *d)
{
	double	old_dir;
	double	old_plan;
	double	rotspeed;

	rotspeed = 3.0 * d->deltatime;
	old_dir = d->direction.x;
	old_plan = d->cam.x;
	if (d->keys.left) //j'ai inverse les touches (peut-etre a investiguer plus en profondeur)
	{
		d->direction.x = d->direction.x * cos(-rotspeed)
			- d->direction.y * sin(-rotspeed);
		d->direction.y = old_dir * sin(-rotspeed)
			+ d->direction.y * cos(-rotspeed);
		d->cam.x = d->cam.x * cos(-rotspeed) - d->cam.y * sin(-rotspeed);
		d->cam.y = old_plan * sin(-rotspeed) + d->cam.y * cos(-rotspeed);
	}
	if (d->keys.right)
	{
		d->direction.x = d->direction.x * cos(rotspeed)
			- d->direction.y * sin(rotspeed);
		d->direction.y = old_dir * sin(rotspeed)
			+ d->direction.y * cos(rotspeed);
		d->cam.x = d->cam.x * cos(rotspeed) - d->cam.y * sin(rotspeed);
		d->cam.y = old_plan * sin(rotspeed) + d->cam.y * cos(rotspeed);
	}
}

t_point	move_player(t_data *d, double movespeed)
{
	t_point	tmp;

	tmp.x = d->player_pos.x;
	tmp.y = d->player_pos.y;
	if (d->keys.w)
	{
		d->player_pos.x += d->direction.x * movespeed;
		d->player_pos.y += d->direction.y * movespeed;
	}
	if (d->keys.s)
	{
		d->player_pos.x -= d->direction.x * movespeed;
		d->player_pos.y -= d->direction.y * movespeed;
	}
	if (d->keys.d)
	{
		d->player_pos.x += -d->direction.y * movespeed;
		d->player_pos.y += d->direction.x * movespeed;
	}
	if (d->keys.a)
	{
		d->player_pos.x += d->direction.y * movespeed;
		d->player_pos.y += -d->direction.x * movespeed;
	}
	return (tmp);
}

void	update_player(t_data *d)
{
	double	movespeed;
	int		idx;
	t_point	tmp;

	movespeed = 2.0 * d->deltatime;
	rotate_player(d);
	tmp = move_player(d, movespeed);
	if (d->map[(int)tmp.y][(int)tmp.x] == 'D')
	{
		idx = door_index_at(d, (int)tmp.x, (int)tmp.y);
		if (idx >= 0 && d->tab_doors && d->tab_doors[idx].lock)
			open_door(d, idx);
	}
	if (d->map[(int)d->player_pos.y][(int)d->player_pos.x] == '1'
	|| (d->map[(int)d->player_pos.y][(int)d->player_pos.x] == 'D'
 		&& door_is_locked_at(d, (int)tmp.x, (int)tmp.y))) //peut-etre a modifier si ca ram comme ne pas "rollback" mais modifier directement le tmp et si c'est bon l'assigner
	{
		d->player_pos.x = tmp.x;
		d->player_pos.y = tmp.y;
	}
}

/*
// Treat pure black (RGB = 0) as transparent
// GATE SHOULD ONLY DRAW IF IT IS CLOSER THAN THE SPRITE
static void draw_gates2(t_data *d, int x, int drawStart, int drawEnd, int texX, double step, double texPos, double dist, t_tex *gateTex)
{
	int y;

	y = drawStart;
	while (y < drawEnd)
    {
        int texY = (int)texPos;
        texPos += step;
        if (texY < 0)
			texY = 0;
        if (texY >= gateTex->height)
			texY = gateTex->height - 1;
        unsigned int color = gateTex->pixels[texY * gateTex->width + texX];
		if ((color & 0x00FFFFFF) != 0) // not transparent
		{
			if (dist < d->pixelDepth[y][x])
			{
				put_px(d, x, y, color | 0xFF000000);
				d->pixelDepth[y][x] = dist;
			}
		}
		y++;
    }
}

// draw from far → near so closer gate overwrites farther
static void draw_gates(t_data *d, int pitch, int SCRN_H)
{
	t_tex *gateTex ;

	int x;

	x= 0;
    while (x < SCRN_W)
    {
		int count = d->gateCount[x];
        if (count <= 0)
			continue;
		int gi = count - 1;
        while (gi >= 0)
        {
            double dist = d->gateLayers[x][gi].dist;
            if (dist <= 0.0)
            	continue;
			gateTex = &d->tex[d->gateLayers[x][gi].locked];
            int lineHeight = (int)(SCRN_H / dist);
            int drawStart = -lineHeight / 2 + SCRN_H / 2 + pitch;
            if (drawStart < 0)
				drawStart = 0;
            int drawEnd = lineHeight / 2 + SCRN_H / 2 + pitch;
            if (drawEnd >= SCRN_H)
				drawEnd = SCRN_H - 1;
            int texX = d->gateLayers[x][gi].texX;
            double step = 1.0 * gateTex->height / lineHeight;
            double texPos = (drawStart - pitch - SCRN_H / 2 + lineHeight / 2) * step;
            draw_gates2(d, x, drawStart, drawEnd, texX, step, texPos, dist, gateTex);
			gi--;
        }
		x++;
    }
}*/

static void draw_gates(t_data *d, int pitch)
{
	t_tex *gateTex ;


    for (int x = 0; x < SCRN_W; ++x)
    {
        int count = d->gateCount[x];
        if (count <= 0)
            continue;
        // draw from far → near so closer gate overwrites farther
        for (int gi = count - 1; gi >= 0; --gi)
        {
            double dist = d->gateLayers[x][gi].dist;
            if (dist <= 0.0)
                continue;
			gateTex = &d->tex[d->gateLayers[x][gi].locked];
            int lineHeight = (int)(SCRN_H / dist);
            int drawStart = -lineHeight / 2 + SCRN_H / 2 + pitch;
            if (drawStart < 0)
				drawStart = 0;
            int drawEnd = lineHeight / 2 + SCRN_H / 2 + pitch;
            if (drawEnd >= SCRN_H)
				drawEnd = SCRN_H - 1;
            int texX = d->gateLayers[x][gi].texX;
            double step = 1.0 * gateTex->height / lineHeight;
            double texPos = (drawStart - pitch - SCRN_H / 2 + lineHeight / 2) * step;
            for (int y = drawStart; y < drawEnd; ++y)
            {
                int texY = (int)texPos;
                texPos += step;
                if (texY < 0)
					texY = 0;
                if (texY >= gateTex->height)
					texY = gateTex->height - 1;
                unsigned int color = gateTex->pixels[texY * gateTex->width + texX];
                // Treat pure black (RGB = 0) as transparent
				if ((color & 0x00FFFFFF) != 0) // not transparent
				{
					// GATE SHOULD ONLY DRAW IF IT IS CLOSER THAN THE SPRITE
					if (dist < d->pixelDepth[y][x])
					{
						put_px(d, x, y, color | 0xFF000000);
						d->pixelDepth[y][x] = dist;
					}
				}
            }
        }
    }
}

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

static void	assign_gate_value(int x, int gate_tex,
		double gatedist, int texx_gate)
{
	t_data	*d;
	int		gi;

	d = get_data();
	if (d->gateCount[x] < d->doors_count)
	{
		gi = d->gateCount[x];
		d->gateLayers[x][gi].dist = gatedist;
		d->gateLayers[x][gi].texX = texx_gate;
		d->gateLayers[x][gi].locked = gate_tex;
		d->gateCount[x]++;
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

int	raycasting(t_data *d)
{
	int		x;
	int		pitch = 100;

	x = 0;
	// reset gate counts for this frame
	for (int i = 0; i < SCRN_W; ++i)
		d->gateCount[i] = 0;
	for (int y = 0; y < SCRN_H; ++y)
    	for (int x2 = 0; x2 < SCRN_W; ++x2)
        	d->pixelDepth[y][x2] = 1e30;
	while (x < SCRN_W)
	{
		first_calc(d, x);
		 //calculate step and initial sideDist
		//perform DDA
		d->hit = 0;
		step_calc(d);
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
		 //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if (d->side == 0)
			d->perpwalldist = (d->sidedistx - d->deltadistx);
		else
			d->perpwalldist = (d->sidedisty - d->deltadisty);
		 //Calculate height of line to draw on screen
		 if (d->perpwalldist < 1e-6)
		 	d->perpwalldist = 1e-6;
		int lineHeight = (int)(SCRN_H / d->perpwalldist);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCRN_H / 2 + pitch;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCRN_H / 2 + pitch;
		if (drawEnd >= SCRN_H)
			drawEnd = SCRN_H - 1;
		for (int y = 0; y < drawStart; ++y)
		{
			if (d->sky.pixels && d->sky.width > 0 && d->sky.height > 0)
			{
				int texX = (int)((double)x * d->sky.width / (double)SCRN_W);
				int texY = (int)((double)y * d->sky.height / (double)SCRN_H);
				unsigned int color = d->sky.pixels[texY * d->sky.width + texX];
				put_px(d, x, y, color | 0xFF000000);
			}
			else
				put_px(d, x, y, CEILING_COLOR);
		}
		 //texturing calculations
		int	texNum = /*d->map[d->mapx][d->mapy]*/ d->cardinal ; //1 subtracted from it so that tex 0 can be used!
		 //calculate value of wallx
		double	wallx; //where exactly the wall was d->hit
		if (d->side == 0)
			wallx = d->player_pos.y + d->perpwalldist * d->raydiry;
		else
			wallx = d->player_pos.x + d->perpwalldist * d->raydirx;
		wallx -= floor((wallx));
		 //x coordinate on the tex
		int texX = (int)(wallx * (double)d->tex[texNum].width);
		if (d->side == 0 && d->raydirx > 0)
			texX = d->tex[texNum].width - texX - 1;
		if (d->side == 1 && d->raydiry < 0)
			texX = d->tex[texNum].width - texX - 1;
		 // TODO: an integer-only bresenham or DDA like algorithm could make the tex coordinate stepping faster
		// How much to increase the tex coordinate per screen pixel
		double step = 1.0 * d->tex[texNum].height / lineHeight;
		// Starting tex coordinate
		double texPos = (drawStart - pitch - SCRN_H / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			//ft_printf(1, "WTHHHHHH OHMAGAAAD Also tex path is %s\n", d->tex[texNum].path);
			// Cast the tex coordinate to integer, and mask with (TEXHEIGHT - 1) in case of overflow
			int texY = (int)texPos & (d->tex[texNum].height - 1);
			texPos += step;
			unsigned int color = d->tex[texNum].pixels[texY * d->tex[texNum].width + texX];
			// unsigned int color = 0xFF0000FF;
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			// if(d->side == 1) color = (color >> 1) & 8355711;
			put_px(d, x, y, color | 0xFF000000);
			d->pixelDepth[y][x] = d->perpwalldist;   // wall is at this distance
		}
		for (int y = drawEnd; y < SCRN_H; ++y)
    		put_px(d, x, y, FLOOR_COLOR);
		x++;
	}
	for (int i = 0; i < d->monster_count; i++)
	{
		t_monster *m = &d->tab_m[i];
		// relative to player
		double spriteX = m->pos.x - d->player_pos.x;
		double spriteY = m->pos.y - d->player_pos.y;
		// inverse determinant of cam matrix
		double invDet = 1.0 / (d->cam.x * d->direction.y
							- d->direction.x * d->cam.y);
		// transform to cam space
		double transformX = invDet * (d->direction.y * spriteX - d->direction.x * spriteY);
		double transformY = invDet * (-d->cam.y * spriteX + d->cam.x * spriteY);
		if (transformY <= 0)
			continue;
		// screen X
		int spriteScreenX = (int)((SCRN_W / 2) * (1 + transformX / transformY));
		// world-space vertical offset (feet height, tune 0.0–0.7)
		double vMove = 0.3;
		int vMoveScreen = (int)(vMove / transformY);   // <-- NO + pitch here
		// sprite dimensions (scale with distance)
		int spriteHeight = abs((int)(SCRN_H / transformY));
		int drawStartY = -spriteHeight / 2 + SCRN_H / 2 + pitch + vMoveScreen;
		if (drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + SCRN_H / 2 + pitch + vMoveScreen;
		if (drawEndY >= SCRN_H) drawEndY = SCRN_H - 1;
		int spriteWidth = abs((int)(SCRN_H / transformY));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= SCRN_W) drawEndX = SCRN_W - 1;
		// draw each vertical stripe of the sprite
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX))
						* d->tex[10].width / spriteWidth) / 256;
			if (texX < 0) texX = 0;
			if (texX >= d->tex[10].width) texX = d->tex[10].width - 1;
			if (transformY > 0 && stripe >= 0 && stripe < SCRN_W)
			{
				for (int y = drawStartY; y < drawEndY; y++)
				{
					int pos = (y - (pitch + vMoveScreen)) * 256
							- SCRN_H * 128
							+ spriteHeight * 128;
					int texY = (pos * d->tex[10].height) / spriteHeight / 256;
					if (texY < 0) texY = 0;
					if (texY >= d->tex[10].height) texY = d->tex[10].height - 1;
					unsigned int color =
						d->tex[10].pixels[texY * d->tex[10].width + texX];
					if ((color & 0x00FFFFFF) != 0) // non-transparent pixel
					{
						// Only draw if sprite is in front of whatever is already there
						if (transformY < d->pixelDepth[y][stripe])
						{
							put_px(d, stripe, y, color | 0xFF000000);
							d->pixelDepth[y][stripe] = transformY;
						}
					}
				// if sprite pixel is transparent: do nothing, don't change pixelDepth
				}
			}
		}
	}
	draw_gates(d, pitch);
	return (0);
}

// int	render_frame(void *param) ----->GRADIENT pour verifier que put_px marche
// {
//     t_data *d = get_data();

//     // simple gradient to test drawing
// 	(void)param;
//     for (int y = 0; y < SCRN_H; ++y)
//     {
//         for (int x = 0; x < SCRN_W; ++x)
//         {
//             unsigned int r = (x * 255) / SCRN_W;
//             unsigned int g = (y * 255) / SCRN_H;
//             unsigned int b = 128;
//             unsigned int color = (r << 16) | (g << 8) | b;

//             // add opaque alpha in case your MLX uses ARGB
//             color |= 0xFF000000;

//             put_px(d, x, y, color);
//         }
//     }

//     mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->mlx_img->img, 0, 0);
//     return 0;
// }

// convert to radians; DO NOT multiply by dt here (event accumulation already reflects real motion)
// clamp huge flicks so it never spins too fast
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
