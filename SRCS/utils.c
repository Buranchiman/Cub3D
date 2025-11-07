/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:03:29 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/05 16:50:41 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

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

void	empty_tab(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
}

void	check_file_format(char *file)
{
	int	i;

	i = 0;
	while (file[i] && file[i] != '.')
		i++;
	if (ft_strncmp(&file[i], ".cub", 5))
	{
		printf("Error\nMap file is not a .cub\n"); //potentiellement sortir ca sur stderr
		exit(EXIT_FAILURE);
	}
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

void	ft_clean_exit(t_data *data, int option, char *msg)
{
	if (data->map)
		ft_clear_tab(data->map);
	empty_tab(data->texture, 6);
	if (data->buffer)
		free(data->buffer);
	//space for clearing images and other allocations
	if (msg && option == 1)
		printf("Error\n%s\n", msg); //potentiellement sortir ca sur stderr
	if (msg && option == 0)
		printf("\n%s\n", msg);
	// if (data->win)
	// 	mlx_destroy_window(data->mlx, data->win);
	// if (data->mlx)
	// {
	// 	mlx_destroy_display(data->mlx);
	// 	free(data->mlx);
	// }
	if (option == 1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
