/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:03:29 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/10 16:57:40 by wivallee         ###   ########.fr       */
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

int	quit_with_int(t_data *data)
{
	if (!data)
		data = get_data();
	ft_clean_exit(data, 0, "See you soon👋");
	return (0);
}

int	doors_count(t_data *data, int x, int y)
{
	int	doors_count;

	doors_count = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'D')
				doors_count++;
			x++;
		}
		y++;
	}
	if (doors_count <= 0)
	{
		data->tab_doors = NULL;
		data->doors_count = 0;
		return (0);
	}
	data->tab_doors = ft_calloc(doors_count, sizeof(*(data->tab_doors)));
	if (!data->tab_doors)
		ft_clean_exit(data, 1, "Malloc failed in doors_count");
	data->doors_count = doors_count;
	return (data->doors_count);
}
