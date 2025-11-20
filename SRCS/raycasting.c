/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:10:34 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/20 18:07:18 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"


static inline void	put_px(t_data *d, int x, int y, unsigned int argb)
{
	if ((unsigned)x >= (unsigned)SCREENWIDTH || (unsigned)y >= (unsigned)SCREENHEIGHT)
		return;
	char *p = d->mlx_img->addr + y * d->mlx_img->line_len + x * (d->mlx_img->bpp / 8);
	*(unsigned int *)p = argb;
}

void	update_player(t_data *d)
{
	double	rotSpeed = 3.0 * d->deltatime; // radians per frame (tune this)
	double	moveSpeed = 2.0 * d->deltatime;
	double	tmpPosX = 0;
	double	tmpPosY = 0;
	// rotate right
	if (d->keys.left) //j'ai inverse les touches (peut-etre a investiguer plus en profondeur)
	{
		double oldDirX = d->direction.x;
		d->direction.x = d->direction.x * cos(-rotSpeed)
			- d->direction.y * sin(-rotSpeed);
		d->direction.y = oldDirX * sin(-rotSpeed)
			+ d->direction.y * cos(-rotSpeed);

		double oldPlaneX = d->cameraplane.x;
		d->cameraplane.x = d->cameraplane.x * cos(-rotSpeed)
			- d->cameraplane.y * sin(-rotSpeed);
		d->cameraplane.y = oldPlaneX * sin(-rotSpeed)
			+ d->cameraplane.y * cos(-rotSpeed);
	}
	// rotate left
	if (d->keys.right)
	{
		double oldDirX = d->direction.x;
		d->direction.x = d->direction.x * cos(rotSpeed)
			- d->direction.y * sin(rotSpeed);
		d->direction.y = oldDirX * sin(rotSpeed)
			+ d->direction.y * cos(rotSpeed);

		double oldPlaneX = d->cameraplane.x;
		d->cameraplane.x = d->cameraplane.x * cos(rotSpeed)
			- d->cameraplane.y * sin(rotSpeed);
		d->cameraplane.y = oldPlaneX * sin(rotSpeed)
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
		int idx;
		idx = door_index_at(d, (int)d->player_pos.x, (int)d->player_pos.y);
		if (idx >= 0 && d->tab_doors && d->tab_doors[idx].lock)
			open_door(d, idx);
	}
	if (d->map[(int)d->player_pos.y][(int)d->player_pos.x] == '1' || (d->map[(int)d->player_pos.y][(int)d->player_pos.x] == 'D'
 		&& door_is_locked_at(d, (int)d->player_pos.x, (int)d->player_pos.y))) //peut-etre a modifier si ca ram comme ne pas "rollback" mais modifier directement le tmp et si c'est bon l'assigner
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

	h = SCREENHEIGHT;
	w = SCREENWIDTH;
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
			if(data->map[mapY][mapX] == '1')
				hit = 1;
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


		int pitch = 100;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2 + pitch;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2 + pitch;
		if (drawEnd >= h)
			drawEnd = h - 1;

		for (int y = 0; y < drawStart; ++y)
			put_px(data, x, y, ceiling_color);
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
		}
		for (int y = drawEnd; y < h; ++y)
    		put_px(data, x, y, floor_color);
		x++;
	}
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

int	render_frame(void *param)
{
	t_data	*data;
	double	now;

	(void)param;
	data = get_data();
	now = get_time();
	data->deltatime = now - data->lasttime;
	data->lasttime = now;
	//printf("delta time is %f\n", data->deltatime);
	if (data->deltatime > 0.05)
		data->deltatime = 0.05;
	update_player(data);
	raycasting(data);
	// draw main frame first
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->mlx_img->img, 0, 0);
	// then overlay the minimap on top
	update_minimap(data);
	return (0);
}
