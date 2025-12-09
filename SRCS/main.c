/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillichien <chillichien@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:09 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/09 18:28:23 by chillichien      ###   ########.fr       */
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

int	main(int arc, char **arv)
{
	t_data	*data;

	verif_param(arc, arv);
	get_map(arv[1]);
	data = get_data();
	display_window(data, 0);
	display_minimap(data, 0, 0);
	data->lasttime = get_time();
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
