/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:09 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/14 21:53:33 by manon            ###   ########.fr       */
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

int	loop_hook(t_data *data)
{
	unsigned long	current;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (current - data->last_update < 120UL)//120UL vaut 120 milliseconds
		return (0);
	else
	{
		//⚜️bonus⚜️
		monsters_move(data);
		data->last_update = current;
		if (data->held_key)
			key_hook(data->held_key, data);
	//	data->last_update = current;
	}
	return (0);
}

int	main(int arc, char **arv)
{
	t_data	*data;

	verif_param(arc, arv);
	get_map(arv[1]);
	data = get_data();
	display_window(data);
	display_minimap(data);
	//system("mpg123 --loop -1 -q musique1.mp3 &"); //add music
	//mlx_key_hook(data->win_ptr, key_hook, data);
	mlx_hook(data->win_ptr, 2, 1L<<0, key_press, data);
	mlx_hook(data->win_ptr, 3, 1L<<1, key_release, data);
	mlx_hook(data->win_ptr, 17, 0L, quit_with_int, data);
	mlx_loop_hook(data->mlx_ptr, loop_hook, data);
	mlx_loop(data->mlx_ptr);
	ft_clean_exit(data, 0, NULL);
	return (0);
}
