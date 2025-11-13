/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillichien <chillichien@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:10:34 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/12 14:09:58 by chillichien      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

int	raycasting(t_data *data)
{
	int		w;
	int		x;
	double	rayDirX;
	double	rayDirY;
	int		h;

	h = SCREENHEIGHT;
	w = SCREENWIDTH;
	while (1)
	{
		x = 0;
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
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if(data->map[mapY][mapX] != '0')
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

			 //texturing calculations
			int texNum = /*data->map[mapX][mapY]*/ 0 ; //1 subtracted from it so that texture 0 can be used!

			 //calculate value of wallX
			double wallX; //where exactly the wall was hit
			if (side == 0)
				wallX = data->player_pos.y + perpWallDist * rayDirY;
			else
				wallX = data->player_pos.x + perpWallDist * rayDirX;
			wallX -= floor((wallX));

			 //x coordinate on the texture
			int texX = (int)(wallX * (double)TEXWIDTH);
			if(side == 0 && rayDirX > 0)
				texX = TEXWIDTH - texX - 1;
			if(side == 1 && rayDirY < 0)
				texX = TEXWIDTH - texX - 1;

			 // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
			// How much to increase the texture coordinate per screen pixel
			double step = 1.0 * TEXHEIGHT / lineHeight;
			// Starting texture coordinate
			double texPos = (drawStart - pitch - h / 2 + lineHeight / 2) * step;
			for(int y = drawStart; y < drawEnd; y++)
			{
				// Cast the texture coordinate to integer, and mask with (TEXHEIGHT - 1) in case of overflow
				int texY = (int)texPos & (TEXHEIGHT - 1);
				texPos += step;
				Uint32 color = data->texture[texNum][TEXWIDTH * texY + texX];
				//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
				if(side == 1) color = (color >> 1) & 8355711;
					buffer[y][x] = color;
			}
			x++;
		}
	}
}
