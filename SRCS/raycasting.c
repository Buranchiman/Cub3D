/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:10:34 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/02 15:48:45 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

static inline void	put_px(t_data *d, int x, int y, unsigned int argb)
{
	char	*p;

	if ((unsigned)x >= (unsigned)SCREENWIDTH
		|| (unsigned)y >= (unsigned)SCREENHEIGHT)
		return ;
	p = d->mlx_img->addr + y * d->mlx_img->line_len + x * (d->mlx_img->bpp / 8);
	*(unsigned int *)p = argb;
}

static int	fetch_texture(char c, int x, int y)
{
	t_data	*d;
	int		idx;

	d = get_data();
	if (c == 'D')
	{
		idx = door_index_at(d, x, y);
		printf("index of door is %d\n", idx);
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

static void draw_gates(t_data *data, int pitch, int h)
{
	t_texture *gateTex ;


    for (int x = 0; x < SCREENWIDTH; ++x)
    {
        int count = data->gateCount[x];
        if (count <= 0)
            continue;

        // draw from far → near so closer gate overwrites farther
        for (int gi = count - 1; gi >= 0; --gi)
        {
            double dist = data->gateLayers[x][gi].dist;
            if (dist <= 0.0)
                continue;
			gateTex = &data->texture[data->gateLayers[x][gi].locked];
            int lineHeight = (int)(h / dist);

            int drawStart = -lineHeight / 2 + h / 2 + pitch;
            if (drawStart < 0) drawStart = 0;

            int drawEnd = lineHeight / 2 + h / 2 + pitch;
            if (drawEnd >= h) drawEnd = h - 1;

            int texX = data->gateLayers[x][gi].texX;

            double step = 1.0 * gateTex->height / lineHeight;
            double texPos = (drawStart - pitch - h / 2 + lineHeight / 2) * step;

            for (int y = drawStart; y < drawEnd; ++y)
            {
                int texY = (int)texPos;
                texPos += step;

                if (texY < 0) texY = 0;
                if (texY >= gateTex->height) texY = gateTex->height - 1;

                unsigned int color =
                    gateTex->pixels[texY * gateTex->width + texX];

                // Treat pure black (RGB = 0) as transparent
				if ((color & 0x00FFFFFF) != 0) // not transparent
				{
					// GATE SHOULD ONLY DRAW IF IT IS CLOSER THAN THE SPRITE
					if (dist < data->pixelDepth[y][x])
					{
						put_px(data, x, y, color | 0xFF000000);
						data->pixelDepth[y][x] = dist;
					}
				}
            }
        }
    }
}


int	raycasting(t_data *data)
{
	int		w;
	int		x;
	double	rayDirX;
	double	rayDirY;
	int		h;
	double ZBuffer[SCREENWIDTH];
	int pitch = 100;

	h = SCREENHEIGHT;
	w = SCREENWIDTH;
	x = 0;
	unsigned int ceiling_color = 0xFF87CEEB;  // sky
	unsigned int floor_color   = 0xFF444444;  // floor
	// reset gate counts for this frame
	for (int i = 0; i < SCREENWIDTH; ++i)
		data->gateCount[i] = 0;
	for (int y = 0; y < h; ++y)
    	for (int x2 = 0; x2 < w; ++x2)
        	data->pixelDepth[y][x2] = 1e30;
	while (x < w)
	{
		//calculate ray position and direction
		double camX = 2 * x / (double)w - 1; //x-coordinate in cam space
		rayDirX = data->direction.x + data->cam.x * camX;
		rayDirY = data->direction.y + data->cam.y * camX;

		//which box of the map we're in
		int mapX = (int)data->player_pos.x;
		int mapY = (int)data->player_pos.y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? HUGE_VAL : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? HUGE_VAL : fabs(1 / rayDirY);
		double perpWallDist;

		 //what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		 //calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->player_pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->player_pos.x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->player_pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->player_pos.y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
				if (stepX == 1)
					data->cardinal = CARDEAST;
				else
					data->cardinal = CARDWEST;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
				if (stepY == 1)
					data->cardinal = CARDNORTH;
				else
					data->cardinal = CARDSOUTH;
			}
			//Check if ray has hit a wall
			char tile = data->map[mapY][mapX];
			if (tile == 'D') // transparent gate tile
			{
				int	gate_tex;

				if (door_is_locked_at(data, mapX, mapY))
					gate_tex = 11;
				else
					gate_tex = 12;
				// distance to this gate
				double gateDist = (side == 0)
					? (sideDistX - deltaDistX)
					: (sideDistY - deltaDistY);

				// compute where on the texture we hit (like walls)
				double wallX;
				if (side == 0)
					wallX = data->player_pos.y + gateDist * rayDirY;
				else
					wallX = data->player_pos.x + gateDist * rayDirX;
				wallX -= floor(wallX);

				int texX_gate = (int)(wallX * (double)data->texture[gate_tex].width);
				if (texX_gate < 0) texX_gate = 0;
				if (texX_gate >= data->texture[gate_tex].width)
					texX_gate = data->texture[gate_tex].width - 1;

				// store this gate layer for this column
				if (data->gateCount[x] < MAX_GATES_PER_COLUMN)
				{
					int gi = data->gateCount[x];
					data->gateLayers[x][gi].dist = gateDist;
					data->gateLayers[x][gi].texX = texX_gate;
					data->gateLayers[x][gi].locked = gate_tex;
					data->gateCount[x]++;
				}

				// DO NOT mark hit, this gate is not a blocking wall
				continue;
			}
			else if (tile == '1')
			{
				// solid wall or door: stop ray here
				data->cardinal = fetch_texture(tile, mapX, mapY);
				hit = 1;
			}
		}

		 //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		 //Calculate height of line to draw on screen
		 if (perpWallDist < 1e-6)
		 	perpWallDist = 1e-6;
		int lineHeight = (int)(h / perpWallDist);
		ZBuffer[x] = perpWallDist;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2 + pitch;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2 + pitch;
		if (drawEnd >= h)
			drawEnd = h - 1;

		for (int y = 0; y < drawStart; ++y)
		{
			if (data->sky_texture.pixels && data->sky_texture.width > 0 && data->sky_texture.height > 0)
			{
				int texX = (int)((double)x * data->sky_texture.width / (double)SCREENWIDTH);
				int texY = (int)((double)y * data->sky_texture.height / (double)SCREENHEIGHT);
				unsigned int color = data->sky_texture.pixels[texY * data->sky_texture.width + texX];
				put_px(data, x, y, color | 0xFF000000);
			}
			else
				put_px(data, x, y, ceiling_color);
		}
		 //texturing calculations
		int	texNum = /*data->map[mapX][mapY]*/ data->cardinal ; //1 subtracted from it so that texture 0 can be used!

		 //calculate value of wallX
		double	wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = data->player_pos.y + perpWallDist * rayDirY;
		else
			wallX = data->player_pos.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		 //x coordinate on the texture
		int texX = (int)(wallX * (double)data->texture[texNum].width);
		if (side == 0 && rayDirX > 0)
			texX = data->texture[texNum].width - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = data->texture[texNum].width - texX - 1;

		 // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * data->texture[texNum].height / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - pitch - h / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			//ft_printf(1, "WTHHHHHH OHMAGAAAD Also texture path is %s\n", data->texture[texNum].path);
			// Cast the texture coordinate to integer, and mask with (TEXHEIGHT - 1) in case of overflow
			int texY = (int)texPos & (data->texture[texNum].height - 1);
			texPos += step;
			unsigned int color = data->texture[texNum].pixels[texY * data->texture[texNum].width + texX];
			// unsigned int color = 0xFF0000FF;
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			// if(side == 1) color = (color >> 1) & 8355711;
			put_px(data, x, y, color | 0xFF000000);
			data->pixelDepth[y][x] = perpWallDist;   // wall is at this distance
		}
		for (int y = drawEnd; y < h; ++y)
    		put_px(data, x, y, floor_color);
		x++;
	}
	for (int i = 0; i < data->monster_count; i++)
{
    t_monster *m = &data->tab_monsters[i];

    // relative to player
    double spriteX = m->pos.x - data->player_pos.x;
    double spriteY = m->pos.y - data->player_pos.y;

    // inverse determinant of cam matrix
    double invDet = 1.0 / (data->cam.x * data->direction.y
                        - data->direction.x * data->cam.y);

    // transform to cam space
    double transformX = invDet * (data->direction.y * spriteX - data->direction.x * spriteY);
    double transformY = invDet * (-data->cam.y * spriteX + data->cam.x * spriteY);

    if (transformY <= 0)
        continue;

    // screen X
    int spriteScreenX = (int)((SCREENWIDTH / 2) * (1 + transformX / transformY));

    // world-space vertical offset (feet height, tune 0.0–0.7)
    double vMove = 0.3;
    int vMoveScreen = (int)(vMove / transformY);   // <-- NO + pitch here

    // sprite dimensions (scale with distance)
    int spriteHeight = abs((int)(SCREENHEIGHT / transformY));
    int drawStartY = -spriteHeight / 2 + SCREENHEIGHT / 2 + pitch + vMoveScreen;
    if (drawStartY < 0) drawStartY = 0;
    int drawEndY = spriteHeight / 2 + SCREENHEIGHT / 2 + pitch + vMoveScreen;
    if (drawEndY >= SCREENHEIGHT) drawEndY = SCREENHEIGHT - 1;

    int spriteWidth = abs((int)(SCREENHEIGHT / transformY));
    int drawStartX = -spriteWidth / 2 + spriteScreenX;
    if (drawStartX < 0) drawStartX = 0;
    int drawEndX = spriteWidth / 2 + spriteScreenX;
    if (drawEndX >= SCREENWIDTH) drawEndX = SCREENWIDTH - 1;

    // draw each vertical stripe of the sprite
    for (int stripe = drawStartX; stripe < drawEndX; stripe++)
    {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX))
                    * data->texture[10].width / spriteWidth) / 256;
        if (texX < 0) texX = 0;
        if (texX >= data->texture[10].width) texX = data->texture[10].width - 1;

        if (transformY > 0 && stripe >= 0 && stripe < SCREENWIDTH)
	{
		for (int y = drawStartY; y < drawEndY; y++)
		{
			int d = (y - (pitch + vMoveScreen)) * 256
					- SCREENHEIGHT * 128
					+ spriteHeight * 128;
			int texY = (d * data->texture[10].height) / spriteHeight / 256;
			if (texY < 0) texY = 0;
			if (texY >= data->texture[10].height) texY = data->texture[10].height - 1;

			unsigned int color =
				data->texture[10].pixels[texY * data->texture[10].width + texX];

			if ((color & 0x00FFFFFF) != 0) // non-transparent pixel
			{
				// Only draw if sprite is in front of whatever is already there
				if (transformY < data->pixelDepth[y][stripe])
				{
					put_px(data, stripe, y, color | 0xFF000000);
					data->pixelDepth[y][stripe] = transformY;
				}
			}
			// if sprite pixel is transparent: do nothing, don't change pixelDepth
		}
	}
    }
}
	draw_gates(data, pitch, h);
	return (0);
}

// int	render_frame(void *param) ----->GRADIENT pour verifier que put_px marche
// {
//     t_data *d = get_data();

//     // simple gradient to test drawing
// 	(void)param;
//     for (int y = 0; y < SCREENHEIGHT; ++y)
//     {
//         for (int x = 0; x < SCREENWIDTH; ++x)
//         {
//             unsigned int r = (x * 255) / SCREENWIDTH;
//             unsigned int g = (y * 255) / SCREENHEIGHT;
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

void	mouse_rotation(t_data *data)
{
	int		dx;
	double	rot;
	double	c;
	double	s;
	double	old_dir;
	double	old_plan;

	dx = data->mouse_dx;
	data->mouse_dx = 0;
	// convert to radians; DO NOT multiply by dt here (event accumulation already reflects real motion)
	rot = dx * data->mouse_sens;
	// clamp huge flicks so it never spins too fast
	if (rot > data->max_rot_frame)
		rot = data->max_rot_frame;
	if (rot < -data->max_rot_frame)
	rot = -data->max_rot_frame;
	if (rot != 0.0)
	{
		c = cos(rot);
		s = sin(rot);
		old_dir = data->direction.x;
		data->direction.x = data->direction.x * c - data->direction.y * s;
		data->direction.y = old_dir * s + data->direction.y * c;
		old_plan = data->cam.x;
		data->cam.x = data->cam.x * c - data->cam.y * s;
		data->cam.y = old_plan * s + data->cam.y * c;
	}
}

int	render_frame(void *param)
{
	t_data			*data;
	double			now;
	unsigned long	now_ms;

	(void)param;
	data = get_data();
	now = get_time();
	data->deltatime = now - data->lasttime;
	data->lasttime = now;
	now_ms = (unsigned long)(now * 1000.0);
	if (now_ms - data->last_update >= 120UL)
	{
		monsters_move(data);
		data->last_update = now_ms;
	}
	if (data->deltatime > 0.05)
		data->deltatime = 0.05;
	mouse_rotation(data);
	update_player(data);
	raycasting(data);
	// compose minimap into the main image buffer, then blit once
	display_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->mlx_img->img, 0, 0);
	return (0);
}
