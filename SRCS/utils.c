/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:03:29 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/25 16:46:21 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

size_t	ft_tablen(char **tab)
{
	size_t	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			i++;
	}
	return (i);
}

int	is_all_space_n_ones(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] != '1' && string[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	free_img(t_img *img)
{
	t_data	*d;

	d = get_data();
	if (img)
	{
		if (img->img)
			mlx_destroy_image(d->mlx_ptr, img->img);
		free (img);
	}
}

void	ft_clean_exit(t_data *data, int option, char *msg)
{
	int i;

	i = 0;
	if (data->map)
		ft_clear_tab(data->map);
	if (data->buffer)
		free(data->buffer);
	if (data->mlx_img)
		free_img(data->mlx_img);
	while (i < NBR_TEXTURES)
	{
		if (data->texture[i].ptr)
			free_img(data->texture[i].ptr);
		if (data->texture[i].path)
		{
			free(data->texture[i].path);
			data->texture[i].path = NULL;
		}
		if (data->texture[i].pixels)
			free(data->texture[i].pixels);
		i++;
	}
	if (data->sky_texture.ptr)
		free_img(data->sky_texture.ptr);
	if (data->sky_texture.path)
	{
		free(data->sky_texture.path);
		data->sky_texture.path = NULL;
	}
	if (data->sky_texture.pixels)
		free(data->sky_texture.pixels);
	if (data->sky_fallback_path)
	{
		free(data->sky_fallback_path);
		data->sky_fallback_path = NULL;
	}
	if (data->tab_monsters)
	{
		free(data->tab_monsters);
		data->tab_monsters = NULL;
	}
	if (data->tab_doors)
	{
		free(data->tab_doors);
		data->tab_doors = NULL;
	}
	if (msg && option == 1)
		ft_printf(2, "\x1b[38;5;196m[Error : %s]\033[0m\n", msg);
	if (msg && option == 0)
		ft_printf(1, "\x1b[38;5;55m[%s]\033[0m\n", msg);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	//system("pkill mpg123"); //clean music
	//system("stty sane");
	if (option == 1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int	quit_with_int(t_data *data)
{
	if (!data)
		data = get_data();
	ft_clean_exit(data, 0, "See you soon👋");
	return (0);
}
