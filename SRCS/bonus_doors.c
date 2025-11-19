/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:32:18 by manon             #+#    #+#             */
/*   Updated: 2025/11/19 17:27:20 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

int doors_count(t_data *data)
{
	int y;
	int x;
	int doors_count;

	doors_count = 0;
	y = 0;
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

void init_enigma(t_data *data, int i)
{
		if (i == 0)
		{
			data->tab_doors[i].enigma = "I am ./door. I am a directory.";
			data->tab_doors[i].soluce = "cd ./door";
		}
		else if (i == 1)
		{
			data->tab_doors[i].enigma = "T - S = R | S + S = R | S + S + S = ?";
			data->tab_doors[i].soluce = "T";
		}
		else
		{
			data->tab_doors[i].enigma = "The code is oO0OOo0Oo";
			data->tab_doors[i].soluce = "oO0OOo0Oo";
		}
		data->tab_doors[i].lock = 1;
}

int	door_is_locked_at(t_data *data, int tx, int ty)
{
	int i;

	if (!data->tab_doors || data->doors_count <= 0)
		return (0);
	i = 0;
	while (i < data->doors_count)
	{
		if ((int)data->tab_doors[i].pos.x == tx && (int)data->tab_doors[i].pos.y == ty)
			return (data->tab_doors[i].lock);
		i++;
	}
	return (0);
}

int	door_index_at(t_data *data, int tx, int ty)
{
	int i;

	if (!data->tab_doors || data->doors_count <= 0)
		return (-1);
	i = 0;
	while (i < data->doors_count)
	{
		if ((int)data->tab_doors[i].pos.x == tx && (int)data->tab_doors[i].pos.y == ty)
			return (i);
		i++;
	}
	return (-1);
}

int	open_door(t_data *data, int i)
{
	char *line;

	if (data->tab_doors[i].lock == 0)
		return (0);
	if (data->tab_doors[i].lock == 1)
		printf("[The door is locked]\n");
	printf("[It's written on it: %s]\n", data->tab_doors[i].enigma);
	line = get_next_line(0);
	line[ft_strlen(line) - 1] = '\0';
	if (ft_strncmp(line, data->tab_doors[i].soluce, 100) == 0)
	{
		data->tab_doors[i].lock = 0;
		printf("*An uncomfortable sound come from the door*\n");
		return (1);
	}
	else
		printf("[The door doesn't move.]\n");
	return (0);
}

void	doors_init(t_data *data)
{
	int y;
	int x;
	int i;

	i = 0;
	y = 0;
	if (!doors_count(data))
		return ;
	if (!data->tab_doors)
		ft_clean_exit(data, 1, "tab_doors NULL in doors_init");
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'D')
			{
				if (i >= data->doors_count)
					ft_clean_exit(data, 1, "Door count mismatch");
				data->tab_doors[i].pos.x = x;
				data->tab_doors[i].pos.y = y;
				init_enigma(data, i);
				i++;
			}
			x++;
		}
		y++;
	}
}
