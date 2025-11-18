/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:09 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/18 12:24:34 by wivallee         ###   ########.fr       */
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
	t_data	*d = param;

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
	return (0);
}

int	on_keyup(int keycode, void *param)
{
	t_data	*d = param;

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
	return (0);
}


int	main(int arc, char **arv)
{
	t_data	*data;

	verif_param(arc, arv);
	get_map(arv[1]);
	data = get_data();
	display_window(data);
	//display_minimap(data);
	data->mlx_img->img = mlx_new_image(data->mlx_ptr, SCREENWIDTH, SCREENHEIGHT);
	data->mlx_img->addr = mlx_get_data_addr(data->mlx_img->img, &data->mlx_img->bpp, &data->mlx_img->line_len, &data->mlx_img->endian);
	//update_minimap(&data);
	mlx_hook(data->win_ptr, 2, 1L<<0, on_keydown, data);
	mlx_hook(data->win_ptr, 3, 1L<<1, on_keyup, data);
	mlx_loop_hook(data->mlx_ptr, render_frame, data);
	///mlx_key_hook(data->win_ptr, key_hook, data);
	//mlx_hook(data->win_ptr, 17, 0L, quit_with_int, data);
	// mlx_loop_hook(data->mlx_ptr, loop_hook, data);
	mlx_loop(data->mlx_ptr);
	ft_clean_exit(data, 0, NULL);
	return (0);
}
