/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:52:52 by manon             #+#    #+#             */
/*   Updated: 2025/11/04 17:03:21 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../INCLUDE/cube.h"


char	**get_map(char *argv, t_map *map)
{
	int		fd;

	map->stash = NULL;
	fd = open(argv, O_RDONLY);
	if (fd <= 0 || !fd)
		return (ft_printf("⚠️ [Fichier map de taille invalide]\n"), NULL);
	map->line = get_next_line(fd);
	if (map->line == NULL)
		return (ft_printf("⚠️ [Fichier map vide]\n"), NULL);
	while(map->line)
	{
		map->tmp = map->stash;
		if (!map->stash)
		map->stash = ft_strdup(map->line);
		else
		map->stash = ft_strjoin(map->stash, map->line);
		free(map->tmp);
		free(map->line);
		map->line = get_next_line(fd);
	}
	close(fd);
	map->data = ft_split(map->stash, '\n');
	free(map->stash);
	return (map->data);
}


void	draw(t_game *game, int x, int y)
{
	if (y == 0)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->edge1.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (y == game->map->height - 1)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->edge2.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (x == 0)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->edge3.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (x == game->map->width - 1)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->edge4.ptr, x * IMG_SIZE, y * IMG_SIZE);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map->data[y])
	{
		x = 0;
		while (game->map->data[y][x])
		{
			draw_(game, x, y);
			x++;
		}
		y++;
	}
	display_moves(game);
}

void	supp_edge(t_game *game)
{
	//system("pkill mpg123");
	//system("stty sane");
	if (game->edge_corner1.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge_corner1.ptr);
	if (game->edge_corner2.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge_corner2.ptr);
	if (game->edge_corner3.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge_corner3.ptr);
	if (game->edge_corner4.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge_corner4.ptr);
	if (game->edge1.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge1.ptr);
	if (game->edge2.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge2.ptr);
	if (game->edge3.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge3.ptr);
	if (game->edge4.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge4.ptr);
	if (game->black_tile.ptr)
		mlx_destroy_image(game->mlx_ptr, game->black_tile.ptr);
}

int	close_window(t_game *game)
{
	quit_game(game);
	return (1);
}