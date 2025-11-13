/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:03:29 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/11 14:07:48 by mlemerci         ###   ########.fr       */
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
	int i;

	i = 0;
	if (data->map)
		ft_clear_tab(data->map);
	if (data->buffer)
		free(data->buffer);
	while (i < NBR_TEXTURES)
	{
		if (data->texture[i].ptr)	
			mlx_destroy_image(data->mlx_ptr, data->texture[i].ptr);
		if (data->texture[i].path)
		{
			free(data->texture[i].path);
			data->texture[i].path = NULL;
		}
		i++;
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
	if (option == 1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int quit_with_int(t_data *data)
{
	ft_clean_exit(data, 0, "See you soon👋");
	return (0);
}
