/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:03:29 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/08 16:44:06 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

// unsigned long	get_time(void)
// {
// 	struct timeval	tv;
// 	unsigned long	time;

// 	gettimeofday(&tv, NULL);
// 	time = tv.tv_sec * 1000UL + tv.tv_usec / 1000UL;
// 	return (time);
// }

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


void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < NBR_TEXTURES)
	{
		if (data->tex[i].ptr)
			free_img(data->tex[i].ptr);
		if (data->tex[i].path)
			free(data->tex[i].path);
		if (data->tex[i].pixels)
			free(data->tex[i].pixels);
		i++;
	}
	if (data->sky.ptr)
		free_img(data->sky.ptr);
	if (data->sky.path)
		free(data->sky.path);
	if (data->sky.pixels)
		free(data->sky.pixels);
	if (data->sky_path)
		free(data->sky_path);
	if (data->tab_m)
		free(data->tab_m);
	if (data->tab_doors)
		free(data->tab_doors);
}

void	ft_clean_exit(t_data *data, int option, char *msg)
{
	free_data(data);
	if (data->map)
		ft_clear_tab(data->map);
	if (data->buffer)
		free(data->buffer);
	if (data->mlx_img)
		free_img(data->mlx_img);
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
	system("pkill mpg123");
	system("stty sane");
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
