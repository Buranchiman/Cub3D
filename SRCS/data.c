/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:42:04 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/20 19:56:24 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

t_img	*init_img()
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	return (img);
}

void	init_data(void)
{
	t_data	*data;

	data = get_data();
	ft_bzero(data, sizeof(t_data));
	data->player_pos.x = -1;
	data->player_pos.y = -1;
	data->mlx_img = init_img();
}
