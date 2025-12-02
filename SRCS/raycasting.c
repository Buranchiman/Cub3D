/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:10:34 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/02 02:09:19 by manon            ###   ########.fr       */
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

static int	fetch_texture(char c, int x, int y)
{
	t_data	*d;
	int	idx;

	d = get_data();
	if (c == 'D')
	{
		idx = door_index_at(d, x, y);
		if (idx >= 0 && d->tab_doors && d->tab_doors[idx].lock)
			return (11);
		else if (idx >= 0 && d->tab_doors && !d->tab_doors[idx].lock)
			return (12);
	}
	return (d->cardinal);
}

void	update_player(t_data *d)
{
	double	rotSpeed = 3.0 * d->deltatime; // radians per frame (tune this)
	double	moveSpeed = 2.0 * d->deltatime;
	double	tmpPosX = 0;
	double	tmpPosY = 0;
	int 	idx;
	// rotate right
	if (d->keys.left) //j'ai inverse les touches (peut-etre a investiguer plus en profondeur)
	{
		double old_dirx = d->direction.x;
		d->direction.x = d->direction.x * cos(-rotSpeed)
			- d->direction.y * sin(-rotSpeed);
		d->direction.y = old_dirx * sin(-rotSpeed)
			+ d->direction.y * cos(-rotSpeed);

		double old_planex = d->cameraplane.x;
		d->cameraplane.x = d->cameraplane.x * cos(-rotSpeed)
			- d->cameraplane.y * sin(-rotSpeed);
		d->cameraplane.y = old_planex * sin(-rotSpeed)
			+ d->cameraplane.y * cos(-rotSpeed);
	}
	// rotate left
	if (d->keys.right)
	{
		double old_dirx = d->direction.x;
		d->direction.x = d->direction.x * cos(rotSpeed)
			- d->direction.y * sin(rotSpeed);
		d->direction.y = old_dirx * sin(rotSpeed)
			+ d->direction.y * cos(rotSpeed);

		double old_planex = d->cameraplane.x;
		d->cameraplane.x = d->cameraplane.x * cos(rotSpeed)
			- d->cameraplane.y * sin(rotSpeed);
		d->cameraplane.y = old_planex * sin(rotSpeed)
			+ d->cameraplane.y * cos(rotSpeed);
	}
	tmpPosX = d->player_pos.x;
	tmpPosY = d->player_pos.y;
	if (d->keys.w)
	{
		d->player_pos.x += d->direction.x * moveSpeed;
		d->player_pos.y += d->direction.y * moveSpeed;
	}
	if (d->keys.s)
	{
		d->player_pos.x -= d->direction.x * moveSpeed;
		d->player_pos.y -= d->direction.y * moveSpeed;
	}
	if (d->keys.d)
	{
		d->player_pos.x += -d->direction.y * moveSpeed;
		d->player_pos.y += d->direction.x * moveSpeed;
	}
	if (d->keys.a)
	{
		d->player_pos.x += d->direction.y * moveSpeed;
		d->player_pos.y += -d->direction.x * moveSpeed;
	}
	if (d->map[(int)d->player_pos.y][(int)d->player_pos.x] == 'D')
	{
		idx = door_index_at(d, (int)d->player_pos.x, (int)d->player_pos.y);
		if (idx >= 0 && d->tab_doors && d->tab_doors[idx].lock)
			open_door(d, idx);
	}
	if (d->map[(int)d->player_pos.y][(int)d->player_pos.x] == '1' || (d->map[(int)d->player_pos.y][(int)d->player_pos.x] == 'D'
 		&& door_is_locked_at(d, (int)d->player_pos.x, (int)d->player_pos.y)))
	{
		d->player_pos.x = tmpPosX;
		d->player_pos.y = tmpPosY;
	}
}

int	raycasting(t_data *data)
{
	int		w;
	int		x;
	double	rayDirX;
	double	rayDirY;
	int		h;
	double ZBuffer[SCRN_W];
	int pitch = 100;

	h = SCRN_H;
	w = SCRN_W;
	x = 0;
	unsigned int ceiling_color = 0xFF87CEEB;  // sky
	unsigned int floor_color   = 0xFF444444;  // floor

	while (x < w)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		rayDirX = data->direction.x + data->cameraplane.x * cameraX;
		rayDirY = data->direction.y + data->cameraplane.y * cameraX;

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
			if(data->map[mapY][mapX] == '1' || data->map[mapY][mapX] == 'D')
			{
				data->cardinal = fetch_texture(data->map[mapY][mapX], mapX, mapY);
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
			if (data->sky.pixels && data->sky.width > 0 && data->sky.height > 0)
			{
				int texX = (int)((double)x * data->sky.width / (double)SCRN_W);
				int texY = (int)((double)y * data->sky.height / (double)SCRN_H);
				unsigned int color = data->sky.pixels[texY * data->sky.width + texX];
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
		int texX = (int)(wallX * (double)data->tex[texNum].width);
		if (side == 0 && rayDirX > 0)
			texX = data->tex[texNum].width - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = data->tex[texNum].width - texX - 1;

		 // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * data->tex[texNum].height / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - pitch - h / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			//ft_printf(1, "WTHHHHHH OHMAGAAAD Also texture path is %s\n", data->tex[texNum].path);
			// Cast the texture coordinate to integer, and mask with (TEXHEIGHT - 1) in case of overflow
			int texY = (int)texPos & (data->tex[texNum].height - 1);
			texPos += step;
			unsigned int color = data->tex[texNum].pixels[texY * data->tex[texNum].width + texX];
			// unsigned int color = 0xFF0000FF;
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			// if(side == 1) color = (color >> 1) & 8355711;
			if ((color & 0x00FFFFFF) != 0) // skip transparent pixels
                put_px(data, x, y, color);
		}
		for (int y = drawEnd; y < h; ++y)
    		put_px(data, x, y, floor_color);
		x++;
	}
	// for (int i = 0; i < data->monster_count; i++)
	// {
	// 	t_monster *m = &data->tab_m[i];

	// 	// relative to player
	// 	double spriteX = m->pos.x - data->player_pos.x;
	// 	double spriteY = m->pos.y - data->player_pos.y;

	// 	// inverse determinant of camera matrix
	// 	double invDet = 1.0 / (data->cameraplane.x * data->direction.y
	// 						- data->direction.x * data->cameraplane.y);

	// 	// transform to camera space
	// 	double transformX = invDet * (data->direction.y * spriteX - data->direction.x * spriteY);
	// 	double transformY = invDet * (-data->cameraplane.y * spriteX + data->cameraplane.x * spriteY);

	// 	// project to screen
	// 	int spriteScreenX = (int)((SCRN_W / 2) * (1 + transformX / transformY));
	// 	// world-space vertical offset to adjust "feet" height (tune 0.0–0.7)
	// 	double vMove = 0.3;
	// 	int vMoveScreen = (int)(vMove / transformY) + pitch;
	// 	// sprite dimensions (scale with distance)
	// 	int spriteHeight = abs((int)(SCRN_H / transformY));
	// 	int drawStartY = -spriteHeight / 2 + SCRN_H / 2 + vMoveScreen;
	// 	if (drawStartY < 0) drawStartY = 0;
	// 	int drawEndY = spriteHeight / 2 + SCRN_H / 2 + vMoveScreen;
	// 	if (drawEndY >= SCRN_H) drawEndY = SCRN_H - 1;

	// 	int spriteWidth = abs((int)(SCRN_H / transformY));
	// 	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	// 	if (drawStartX < 0) drawStartX = 0;
	// 	int drawEndX = spriteWidth / 2 + spriteScreenX;
	// 	if (drawEndX >= SCRN_W) drawEndX = SCRN_W - 1;

	// 	// draw each vertical stripe of the sprite
	// 	for (int stripe = drawStartX; stripe < drawEndX; stripe++)
	// 	{
	// 		int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX))
	// 					* data->tex[10].width / spriteWidth) / 256;
	// 		if (texX < 0) texX = 0;
	// 		if (texX >= data->tex[10].width) texX = data->tex[10].width - 1;

	// 		if (transformY > 0 && stripe >= 0 && stripe < SCRN_W && transformY < ZBuffer[stripe])
	// 		{
	// 			for (int y = drawStartY; y < drawEndY; y++)
	// 			{
	// 				int d = (y - (pitch + vMoveScreen)) * 256 - SCRN_H * 128 + spriteHeight * 128;
	// 				int texY = ((d * data->tex[10].height) / spriteHeight) / 256;
	// 				if (texY < 0) texY = 0;
	// 				if (texY >= data->tex[10].height) texY = data->tex[10].height - 1;
	// 				unsigned int color = data->tex[10].pixels[texY * data->tex[10].width + texX];
	// 				if ((color & 0x00FFFFFF) != 0) // skip transparent pixels
	// 					put_px(data, stripe, y, color);
	// 			}
	// 		}
	// 	}
	// }
	for (int i = 0; i < data->monster_count; i++)
{
    t_monster *m = &data->tab_m[i];

    // relative to player
    double spriteX = m->pos.x - data->player_pos.x;
    double spriteY = m->pos.y - data->player_pos.y;

    // inverse determinant of camera matrix
    double invDet = 1.0 / (data->cameraplane.x * data->direction.y
                        - data->direction.x * data->cameraplane.y);

    // transform to camera space
    double transformX = invDet * (data->direction.y * spriteX - data->direction.x * spriteY);
    double transformY = invDet * (-data->cameraplane.y * spriteX + data->cameraplane.x * spriteY);

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
                    * data->tex[10].width / spriteWidth) / 256;
        if (texX < 0) texX = 0;
        if (texX >= data->tex[10].width) texX = data->tex[10].width - 1;

        if (transformY > 0 && stripe >= 0 && stripe < SCRN_W && transformY < ZBuffer[stripe])
        {
            for (int y = drawStartY; y < drawEndY; y++)
            {
                int d = (y - (pitch + vMoveScreen)) * 256
                        - SCRN_H * 128
                        + spriteHeight * 128;
                int texY = (d * data->tex[10].height) / spriteHeight / 256;
                if (texY < 0) texY = 0;
                if (texY >= data->tex[10].height) texY = data->tex[10].height - 1;

                unsigned int color = data->tex[10].pixels[texY * data->tex[10].width + texX];
                if ((color & 0x00FFFFFF) != 0) // skip transparent pixels
                    put_px(data, stripe, y, color);
            }
        }
    }
}

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

void	mouse_rotation(t_data *data)
{
	int		dx;
	double	rot;
	double	c;
	double	s;
	double	old_dirx;
	double	old_planex;

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
		old_dirx = data->direction.x;
		data->direction.x = data->direction.x * c - data->direction.y * s;
		data->direction.y = old_dirx * s + data->direction.y * c;
		old_planex = data->cameraplane.x;
		data->cameraplane.x = data->cameraplane.x * c - data->cameraplane.y * s;
		data->cameraplane.y = old_planex * s + data->cameraplane.y * c;
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
	display_minimap(data, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->mlx_img->img, 0, 0);
	return (0);
}
