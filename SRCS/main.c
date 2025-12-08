/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:09 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/08 15:13:25 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	verif_param(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Wrong number of arguments");
		exit(1);
	}
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
	{
		printf("File map is not .cub");
		exit(1);
	}
}

int	on_keydown(int keycode, void *param)
{
	t_data	*d;

	d = param;
	if (keycode == KEY_LEFT)
		d->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		d->keys.right = 1;
	else if (keycode == KEY_W)
		d->keys.w = 1;
	else if (keycode == KEY_A)
		d->keys.a = 1;
	else if (keycode == KEY_S)
		d->keys.s = 1;
	else if (keycode == KEY_D)
		d->keys.d = 1;
	else if (keycode == KEY_E)
		d->keys.e = 1;
	return (0);
}

int	on_keyup(int keycode, void *param)
{
	t_data	*d = param;

	if (keycode == KEY_ESC)
		ft_clean_exit(get_data(), 0, "See you soon👋");
	if (keycode == KEY_LEFT)
		d->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		d->keys.right = 0;
	else if (keycode == KEY_W)
		d->keys.w = 0;
	else if (keycode == KEY_A)
		d->keys.a = 0;
	else if (keycode == KEY_S)
		d->keys.s = 0;
	else if (keycode == KEY_D)
		d->keys.d = 0;
	else if (keycode == KEY_E)
		d->keys.e = 0;
	return (0);
}

// int mouse_move(int x, int y, t_data *d)
// {
//     static int  first = 1;
//     int         centerX = SCRN_W / 2;
//     int         centerY = SCRN_H / 2;
//     (void)y;

//     if (first)
//     {
//         mlx_mouse_move(d->mlx_ptr, d->win_ptr, centerX, centerY);
//         first = 0;
//         return (0);
//     }

//     int delta_x = x - centerX;
//     if (delta_x == 0)
//         return (0);

//     /* ----------------------------
//        Sensitivity tuning
//        Lower = slower turn
//        Typical good range: 0.001 → 0.004
//     ---------------------------- */
//     double mouse_sens = 0.0025;

//     /* fixed-time rotation (don’t scale by deltatime,
//        MLX event frequency already depends on real time) */
//     double rot = delta_x * mouse_sens;

//     /* Clamp large flicks */
//     if (rot > 0.1)  rot = 0.1;
//     if (rot < -0.1) rot = -0.1;

//     /* Rotate cam */
//     double oldDirX = d->direction.x;
//     d->direction.x = d->direction.x * cos(rot) - d->direction.y * sin(rot);
//     d->direction.y = oldDirX * sin(rot) + d->direction.y * cos(rot);

//     double oldPlaneX = d->cam.x;
//     d->cam.x = d->cam.x * cos(rot) - d->cam.y * sin(rot);
//     d->cam.y = oldPlaneX * sin(rot) + d->cam.y * cos(rot);

//     mlx_mouse_move(d->mlx_ptr, d->win_ptr, centerX, centerY);
//     return (0);
// }

int	mouse_move(int x, int y, t_data *d)
{
	static int	first = 1;
	int			cx;
	int			cy;
	int			dx;

	(void)y;
	cx = SCRN_W / 2;
	cy = SCRN_H / 2;
	if (first)
	{
		mlx_mouse_move(d->mlx_ptr, d->win_ptr, cx, cy);
		first = 0;
		return (0);
	}
	dx = x - cx;
	if (dx != 0)
	{
		d->mouse_dx += dx;                    // accumulate for this frame
		mlx_mouse_move(d->mlx_ptr, d->win_ptr, cx, cy);  // keep centered
	}
	return (0);
}


int	main(int arc, char **arv)
{
	t_data	*data;

	verif_param(arc, arv);
	get_map(arv[1]);
	data = get_data();
	display_window(data, 0);
	display_minimap(data, 0, 0);
	data->lasttime = get_time();
	data->door_time = data->lasttime;
	//data->monster_time = get_time();
	data->last_update = (unsigned long)(data->lasttime * 1000.0);
	system("mpg123 --loop -1 -q lavanville.mp3 &");
	data->mlx_img->img = mlx_new_image(data->mlx_ptr,
			SCRN_W, SCRN_H);
	data->mlx_img->addr = mlx_get_data_addr(data->mlx_img->img,
			&data->mlx_img->bpp, &data->mlx_img->line_len,
			&data->mlx_img->endian);
	mlx_hook(data->win_ptr, 2, 1L << 0, on_keydown, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, on_keyup, data);
	mlx_hook(data->win_ptr, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->win_ptr, 17, 0L, quit_with_int, data);
	mlx_loop_hook(data->mlx_ptr, render_frame, data);
	mlx_loop(data->mlx_ptr);
	ft_clean_exit(data, 0, NULL);
	return (0);
}
