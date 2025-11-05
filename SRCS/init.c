/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:02:42 by manon             #+#    #+#             */
/*   Updated: 2025/11/05 15:33:46 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	//map->data = NULL;
	//map->width = 0;
	//map->height = 0;
	//map->player_pos.x = 0;
	//map->player_pos.y = 0;
	return (map);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map)
	{
		if (map->data)
		{
			while (map->data[i])
			{
				free(map->data[i]);
				i++;
			}
			free(map->data);
		}
		free(map);
	}
}

static void	load_image(t_data *data, char *path, t_img *img)
{
	img->ptr = mlx_xpm_file_to_image(data->mlx_ptr, path,
			&img->width, &img->height);
	if (!img->ptr)
		ft_printf("⚠️ [Chargement de %s impossible\n]", path);
}

static void	loader(t_data *data)
{
	//load_image(data, IMG_PLAYER, &data->player);
}

int	init_images(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->map->width * IMG_SIZE,
			data->map->height * IMG_SIZE, "Cub3D");
	if (!data->win_ptr)
		return (0);
	//song(data);
	loader(data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	data;

	if (!check_args(argc, argv, &data))
		exit(1);
	data.last_update = 0;
	data.map = init_map();
	if (!data.map)
		return (ft_printf("⚠️ [Allocation map échouée]\n"));
	if (!get_map(argv[1], data.map))
		quit_game(&data);
	count(data.map);
//	if (check_shape(data.map) || check_wall(data.map) || check_other(data.map))
//		return (free_map(data.map), 1);
//	if (!validate_path(data.map))
//		return (free_map(data.map), ft_printf("⚠️ [Map non jouable]\n"), 1);
	if (!init_images(&data))
		return (free_map(data.map), ft_printf("⚠️ [Initialisa° images]\n"), 1);
	render_map(&data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_hook(data.win_ptr, 17, 0L, quit_and_free, &data);
	mlx_loop_hook(data.mlx_ptr, loop_hook, &data);
	mlx_loop(data.mlx_ptr);
	free_map(data.map);
}