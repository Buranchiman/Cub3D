/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:42:04 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/08 15:06:11 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

t_img	*init_img(void)
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
	data->mouse_center_x = SCRN_W / 2;
	data->mouse_center_y = SCRN_H / 2;
	data->mouse_dx = 0;
	data->mouse_sens = 0.0015;   // tune 0.0010–0.0030
	data->max_rot_frame = 0.06;  // per frame cap; try 0.04–0.08
	data->mouse_ready = 0;
	data->direction.x = 0.0; //le perso regarde au nord par defaut c'est pour la norme
	data->direction.y = -1.0;
	data->cam.x = 0.66;
	data->cam.y = 0.0;
	data->pitch = 100;
	data->vmove = 0.3;
}
