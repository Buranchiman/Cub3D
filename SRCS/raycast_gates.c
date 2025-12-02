/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_gates.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:00:00 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/02 15:57:07 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

static void	draw_gate_column(t_data *d, int x, int h, int pitch)
{
	t_texture	*tex;
	int			gi;
	int			count;
	double		dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	double		step;
	double		tex_pos;
	int			y;
	int			tex_y;
	unsigned int	color;

	tex = &d->texture[gate_tex];
	count = d->gateCount[x];
	gi = count - 1;
	while (gi >= 0)
	{
		dist = d->gateLayers[x][gi].dist;
		if (dist > 0.0)
		{
			line_height = (int)(h / dist);
			draw_start = -line_height / 2 + h / 2 + pitch;
			if (draw_start < 0)
				draw_start = 0;
			draw_end = line_height / 2 + h / 2 + pitch;
			if (draw_end >= h)
				draw_end = h - 1;
			tex_x = d->gateLayers[x][gi].texX;
			step = (double)tex->height / (double)line_height;
			tex_pos = (draw_start - pitch - h / 2 + line_height / 2) * step;
			y = draw_start;
			while (y < draw_end)
			{
				tex_y = (int)tex_pos;
				if (tex_y < 0)
					tex_y = 0;
				if (tex_y >= tex->height)
					tex_y = tex->height - 1;
				color = tex->pixels[tex_y * tex->width + tex_x];
				if ((color & 0x00FFFFFF) != 0
					&& dist < d->pixelDepth[y][x])
				{
					put_px(d, x, y, color | 0xFF000000);
					d->pixelDepth[y][x] = dist;
				}
				tex_pos += step;
				y++;
			}
		}
		gi--;
	}
}

void	draw_gates(t_data *data, int pitch, int h)
{
	int	x;

	x = 0;
	while (x < SCRN_W)
	{
		if (data->gateCount[x] > 0)
			draw_gate_column(data, x, h, pitch);
		x++;
	}
}
