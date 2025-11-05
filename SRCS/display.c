/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:52:52 by manon             #+#    #+#             */
/*   Updated: 2025/11/05 15:33:53 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

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


void	draw(t_data *data, int x, int y)
{
	if (y == 0)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->no_text.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (y == data->map->height - 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->so_text.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (x == 0)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->we_text.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (x == data->map->width - 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->ea_text.ptr, x * IMG_SIZE, y * IMG_SIZE);
}

void	render_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->data[y])
	{
		x = 0;
		while (data->map->data[y][x])
		{
			draw_(data, x, y);
			x++;
		}
		y++;
	}
	display_moves(data);
}

void	quit_and_free(t_data *data)
{
	//system("pkill mpg123"); ->si ajout de musique
	//system("stty sane");
	if (data->no_text.ptr)
		mlx_destroy_image(data->mlx_ptr, data->no_text.ptr);
	if (data->so_text.ptr)
		mlx_destroy_image(data->mlx_ptr, data->so_text.ptr);
	if (data->we_text.ptr)
		mlx_destroy_image(data->mlx_ptr, data->we_text.ptr);
	if (data->ea_text.ptr)
		mlx_destroy_image(data->mlx_ptr, data->ea_text.ptr);
	if (data->mlx_ptr && data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(0);
}
