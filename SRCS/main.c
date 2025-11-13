/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillichien <chillichien@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:09 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/12 14:32:49 by chillichien      ###   ########.fr       */
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

//int	loop_hook(t_data *data)
//{
//	//unsigned long	current;
//
//	//current = get_time();
//	//if (current - data->last_update >= 500)
//	{
//		render_map(data);
//		//data->last_update = current;
//		if (data->held_key)
//			key_hook(data->held_key, data);
//	}
//	return (0);
//}

int	main(int arc, char **arv)
{
	t_data	*data;
	int		i;

	i = 0;
	verif_param(arc, arv);
	//check_file_format(arv[1]);
	get_map(arv[1]);
	data = get_data();
	while (data->map[i])
	{
		ft_printf(1, "%s\n", data->map[i]);
		i++;
	}
	display_window(data);
	display_minimap(data);
	data->mlx_img-> img = mlx_new_image(data->mlx_img, SCREENWIDTH, SCREENHEIGHT);
	data->mlx_img->addr = mlx_get_data_addr(data->mlx_img, &data->mlx_img->bpp, &data->mlx_img->line_len, &data->mlx_img->endian);
	//update_minimap(&data);
	mlx_key_hook(data->win_ptr, key_hook, &data); //input
	mlx_hook(data->win_ptr, 17, 0L, quit_with_int, &data);
	//mlx_loop_hook(data->mlx_ptr, loop_hook, &data);
	mlx_loop(data->mlx_ptr);
	ft_clean_exit(data, 0, NULL);
	return (0);
}
