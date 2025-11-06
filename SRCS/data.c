/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:42:04 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/06 15:01:30 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	init_data(void)
{
	static t_data	*data;
	int i;

	i = 0;
	data = get_data();
	data->buffer = NULL;
	data->map = NULL;
	while(data->texture[i])
	{
		data->texture[i].path = NULL;
		data->texture[i].ptr = NULL;
		i++;
	}
}
