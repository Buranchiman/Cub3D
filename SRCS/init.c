/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:02:42 by manon             #+#    #+#             */
/*   Updated: 2025/11/04 17:02:21 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../INCLUDE/cube.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->data = NULL;
	map->width = 0;
	map->height = 0;
	map->count_fish = 0;
	map->count_exit = 0;
	map->count_fisherman = 0;
	map->count_maelstrom = 0;
	map->fisherman_pos.x = 0;
	map->fisherman_pos.y = 0;
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

static void	load_image(t_game *game, char *path, t_img *img)
{
	img->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&img->width, &img->height);
	if (!img->ptr)
		ft_printf("⚠️ [Chargement de %s impossible\n]", path);
}

static void	loader(t_game *game)
{
	load_image(game, IMG_FISHERMAN, &game->fisherman);
	load_image(game, IMG_FISH, &game->fish);
	load_image(game, IMG_MAELSTROM, &game->maelstrom);
	load_image(game, IMG_BRIDGE, &game->bridge);
	load_image(game, IMG_CORAL, &game->coral);
	load_image(game, IMG_EDGE1, &game->edge1);
	load_image(game, IMG_EDGE2, &game->edge2);
	load_image(game, IMG_EDGE3, &game->edge3);
	load_image(game, IMG_EDGE4, &game->edge4);
	load_image(game, IMG_EDGE_CORNER1, &game->edge_corner1);
	load_image(game, IMG_EDGE_CORNER2, &game->edge_corner2);
	load_image(game, IMG_EDGE_CORNER3, &game->edge_corner3);
	load_image(game, IMG_EDGE_CORNER4, &game->edge_corner4);
	load_image(game, IMG_WATER, &game->water);
	load_image(game, IMG_WAVES, &game->waves);
}

int	init_images(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (0);
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			game->map->width * IMG_SIZE,
			game->map->height * IMG_SIZE, "So_long");
	if (!game->win_ptr)
		return (0);
	song(game);
	loader(game);
	init_black_tile(game);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!check_args(argc, argv, &game))
		exit(1);
	init_add_pos(&game);
	init_struct_attributes(&game);
	game.last_update = 0;
	game.map = init_map();
	if (!game.map)
		return (ft_printf("⚠️ [Allocation map échouée]\n"));
	if (!get_map(argv[1], game.map))
		quit_game(&game);
	count(game.map);
	if (check_shape(game.map) || check_wall(game.map) || check_other(game.map))
		return (free_map(game.map), 1);
	if (!validate_path(game.map))
		return (free_map(game.map), ft_printf("⚠️ [Map non jouable]\n"), 1);
	if (!init_images(&game))
		return (free_map(game.map), ft_printf("⚠️ [Initialisa° images]\n"), 1);
	render_map(&game);
	mlx_key_hook(game.win_ptr, key_hook, &game);
	mlx_hook(game.win_ptr, 17, 0L, close_window, &game);
	mlx_loop_hook(game.mlx_ptr, loop_hook, &game);
	mlx_loop(game.mlx_ptr);
	free_map(game.map);
}