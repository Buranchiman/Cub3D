/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:09 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/14 16:48:59 by wivallee         ###   ########.fr       */
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

void	moving(int keycode, t_data *data)
{
	double	movex;
	double	movey;

	movex = 0;
	movey = 0;
	if (keycode == KEY_W && data->map[(int)data->player_pos.y - 1][(int)data->player_pos.x] != '1')
		movey -= 0.2;
	if (keycode == KEY_A && data->map[(int)data->player_pos.y][(int)data->player_pos.x - 1] != '1')
		movex -= 0.2;
	if (keycode == KEY_S && data->map[(int)data->player_pos.y + 1][(int)data->player_pos.x] != '1')
		movey += 0.2;
	if (keycode == KEY_D && data->map[(int)data->player_pos.y][(int)data->player_pos.x + 1] != '1')
		movex += 0.2;
	data->player_pos.x += movex;
	data->player_pos.y += movey;
}

int	key_hook(int keycode, t_data *data)
{
	moving(keycode, data);
	if (keycode == KEY_ESC)
		exit(0);
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
	mlx_loop_hook(data->mlx_ptr, render_frame, data);
	mlx_key_hook(data->win_ptr, key_hook, data);
	//mlx_hook(data->win_ptr, 17, 0L, quit_with_int, data);
	// mlx_loop_hook(data->mlx_ptr, loop_hook, data);
	mlx_loop(data->mlx_ptr);
	ft_clean_exit(data, 0, NULL);
	return (0);
}
