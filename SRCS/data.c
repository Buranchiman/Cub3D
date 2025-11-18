/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:42:04 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/18 15:05:26 by wivallee         ###   ########.fr       */
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
	// data->buffer = NULL;
	// data->map = NULL;
	// data->player_pos.x = -1;
	// data->player_pos.y = -1;
	// data->cameraplane.x = 0;
	// data->cameraplane.y = 0.66;
	// data->direction.x = 0;
	// data->direction.y = 0;
	// data->mlx_ptr = NULL;
	// data->win_ptr = NULL;
	// data->mlx_img = init_img();
	// //a adapter👇
	// while (i <= 9)
	// {
	// 	data->texture[i].path = NULL;
	// 	data->texture[i].ptr = NULL;
	// 	//data->texture[i].width = 32;
	// 	//data->texture[i].height = 32;
	// 	i++;
	// }
	ft_bzero(data, sizeof(t_data));
	data->player_pos.x = -1;
	data->player_pos.y = -1;
	data->mlx_img = init_img();
}
