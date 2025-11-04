/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:42:04 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/04 17:45:48 by wivallee         ###   ########.fr       */
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

	data->buffer = NULL;
	data->map = NULL;
	data->ea_text = NULL;
	data->we_text = NULL;
	data->so_text = NULL;
	data->no_text = NULL;
}
