/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:42:04 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/05 15:46:57 by manon            ###   ########.fr       */
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

	data = get_data();
	data->buffer = NULL;
	data->map = NULL;
	data->texture[0] = NULL;
	data->texture[1] = NULL;
	data->texture[2] = NULL;
	data->texture[3] = NULL;
	data->texture[4] = NULL;
	data->texture[5] = NULL;
}
