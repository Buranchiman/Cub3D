/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:10:34 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/03 14:03:15 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

static void	init_frame(t_data *d, int *h, int *w, int *pitch)
{
	int	x;
	int	y;

	*h = SCRN_H;
	*w = SCRN_W;
	*pitch = 100;
	y = 0;
	while (y < *h)
	{
		x = 0;
		while (x < *w)
		{
			d->pixelDepth[y][x] = 1e30;
			x++;
		}
		y++;
	}
	x = 0;
	while (x < SCRN_W)
	{
		d->gateCount[x] = 0;
		x++;
	}
}

static void	init_ray(t_data *d, int x, int w, double *cam_x, double *rdir)
{
	*cam_x = 2.0 * (double)x / (double)w - 1.0;
	rdir[0] = d->direction.x + d->cam.x * (*cam_x);
	rdir[1] = d->direction.y + d->cam.y * (*cam_x);
}

static void	init_dda(t_data *d, double *rdir, int *map, double *sdist,
		double *ddist)
{
	map[0] = (int)d->player_pos.x;
	map[1] = (int)d->player_pos.y;
	if (rdir[0] == 0.0)
		ddist[0] = HUGE_VAL;
	else
		ddist[0] = fabs(1.0 / rdir[0]);
	if (rdir[1] == 0.0)
		ddist[1] = HUGE_VAL;
	else
		ddist[1] = fabs(1.0 / rdir[1]);
	if (rdir[0] < 0.0)
	{
		map[2] = -1;
		sdist[0] = (d->player_pos.x - map[0]) * ddist[0];
	}
	else
	{
		map[2] = 1;
		sdist[0] = (map[0] + 1.0 - d->player_pos.x) * ddist[0];
	}
	if (rdir[1] < 0.0)
	{
		map[3] = -1;
		sdist[1] = (d->player_pos.y - map[1]) * ddist[1];
	}
	else
	{
		map[3] = 1;
		sdist[1] = (map[1] + 1.0 - d->player_pos.y) * ddist[1];
	}
}

static void	dda_loop(t_data *d, double *sdist, double *ddist, int *map,
		int *side)
{
	int		hit;
	char	tile;
	double	gate_dist;
	double	wall_x;
	int		tex_x;

	hit = 0;
	while (!hit)
	{
		if (sdist[0] < sdist[1])
		{
			sdist[0] += ddist[0];
			map[0] += map[2];
			*side = 0;
			if (map[2] == 1)
				d->cardinal = CARDEAST;
			else
				d->cardinal = CARDWEST;
		}
		else
		{
			sdist[1] += ddist[1];
			map[1] += map[3];
			*side = 1;
			if (map[3] == 1)
				d->cardinal = CARDNORTH;
			else
				d->cardinal = CARDSOUTH;
		}
		tile = d->map[map[1]][map[0]];
		if (tile == 'D')
		{
			if (*side == 0)
				gate_dist = sdist[0] - ddist[0];
			else
				gate_dist = sdist[1] - ddist[1];
			if (*side == 0)
				wall_x = d->player_pos.y + gate_dist * (ddist[1] == HUGE_VAL
						? 0.0 : 1.0 / ddist[1]);
			else
				wall_x = d->player_pos.x + gate_dist * (ddist[0] == HUGE_VAL
						? 0.0 : 1.0 / ddist[0]);
			wall_x -= floor(wall_x);
			tex_x = (int)(wall_x
					* (double)d->tex[gate_tex].width);
			if (tex_x < 0)
				tex_x = 0;
			if (tex_x >= d->tex[gate_tex].width)
				tex_x = d->tex[gate_tex].width - 1;
			if (d->gateCount[map[4]] < data->doors_count)
			{
				d->gateLayers[map[4]][d->gateCount[map[4]]].dist = gate_dist;
				d->gateLayers[map[4]][d->gateCount[map[4]]].texX = tex_x;
				d->gateCount[map[4]]++;
			}
		}
		else if (tile == '1')
		{
			d->cardinal = fetch_tex(tile, map[0], map[1]);
			hit = 1;
		}
	}
}

static void	draw_column(t_data *d, int x, int h, int pitch,
		double perp_dist)
{
	int				line_h;
	int				draw_start;
	int				draw_end;
	int				y;
	unsigned int	ceil_color;
	unsigned int	floor_color;
	double			step;
	double			tex_pos;
	int				tex_x;
	int				tex_y;
	unsigned int	color;
	int				tex_num;
	double			wall_x;
	double			ray_dir_x;
	double			ray_dir_y;

	ceil_color = 0xFF87CEEB;
	floor_color = 0xFF444444;
	line_h = (int)((double)h / perp_dist);
	draw_start = -line_h / 2 + h / 2 + pitch;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_h / 2 + h / 2 + pitch;
	if (draw_end >= h)
		draw_end = h - 1;
	y = 0;
	while (y < draw_start)
	{
		if (d->sky_tex.pixels != NULL
			&& d->sky_tex.width > 0 && d->sky_tex.height > 0)
		{
			tex_x = (int)((double)x * d->sky_tex.width
					/ (double)SCRN_W);
			tex_y = (int)((double)y * d->sky_tex.height
					/ (double)SCRN_H);
			color = d->sky_tex.pixels[tex_y * d->sky_tex.width
				+ tex_x];
			put_px(d, x, y, color | 0xFF000000);
		}
		else
			put_px(d, x, y, ceil_color);
		y++;
	}
	tex_num = d->cardinal;
	ray_dir_x = d->direction.x;
	ray_dir_y = d->direction.y;
	if (ray_dir_x == 0.0)
		ray_dir_x = 0.000001;
	if (ray_dir_y == 0.0)
		ray_dir_y = 0.000001;
	if (d->cardinal == CARDEAST || d->cardinal == CARDWEST)
		wall_x = d->player_pos.y + perp_dist * ray_dir_y;
	else
		wall_x = d->player_pos.x + perp_dist * ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)d->tex[tex_num].width);
	if ((d->cardinal == CARDEAST && ray_dir_x > 0.0)
		|| (d->cardinal == CARDNORTH && ray_dir_y < 0.0))
		tex_x = d->tex[tex_num].width - tex_x - 1;
	step = (double)d->tex[tex_num].height / (double)line_h;
	tex_pos = (draw_start - pitch - h / 2 + line_h / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (d->tex[tex_num].height - 1);
		tex_pos += step;
		color = d->tex[tex_num].pixels[tex_y
			* d->tex[tex_num].width + tex_x];
		put_px(d, x, y, color | 0xFF000000);
		d->pixelDepth[y][x] = perp_dist;
		y++;
	}
	while (y < h)
	{
		put_px(d, x, y, floor_color);
		y++;
	}
}

int	raycasting(t_data *data)
{
	int		h;
	int		w;
	int		pitch;
	int		x;
	double	cam_x;
	double	rdir[2];
	int		map[5];
	double	sdist[2];
	double	ddist[2];
	int		side;
	double	perp_dist;

	init_frame(data, &h, &w, &pitch);
	x = 0;
	while (x < w)
	{
		init_ray(data, x, w, &cam_x, rdir);
		map[4] = x;
		init_dda(data, rdir, map, sdist, ddist);
		dda_loop(data, sdist, ddist, map, &side);
		if (side == 0)
			perp_dist = sdist[0] - ddist[0];
		else
			perp_dist = sdist[1] - ddist[1];
		if (perp_dist < 1e-6)
			perp_dist = 1e-6;
		data->zbuffer[x] = perp_dist;
		draw_column(data, x, h, pitch, perp_dist);
		x++;
	}
	//draw_sprites(data, pitch);
	//draw_gates(data, pitch, h);
	return (0);
}
