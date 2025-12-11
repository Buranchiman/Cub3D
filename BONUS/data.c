/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:42:04 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/11 16:12:46 by wivallee         ###   ########.fr       */
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
	if (!img)
		return (NULL);
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	return (img);
}

// void	set_ray(t_ray *ray)
// {
// 	ray->raydirx = 0;
// 	ray->raydiry = 0;
// 	ray->mapx = 0;
// 	ray->mapy = 0;
// 	ray->sidedistx = 0;
// 	ray->sidedisty = 0;
// 	ray->deltadistx = 0;
// 	ray->deltadisty = 0;
// 	ray->stepx = 0;
// 	ray->stepy = 0;
// 	ray->hit = 0;
// 	ray->side = 0;
// 	ray->perpwalldist = 0;
// 	ray->lineheight = 0;
// 	ray->drawstart = 0;
// 	ray->drawend = 0;
// 	ray->texx = 0;
// 	ray->step = 0;
// 	ray->texpos = 0;
// }

void	init_data(void)
{
	t_data	*data;

	data = get_data();
	ft_bzero(data, sizeof(t_data));
	data->player_pos.x = -1;
	data->player_pos.y = -1;
	data->mlx_img = init_img();
	if (!data->mlx_img)
		ft_clean_exit(data, 1, "Error\nMalloc\n");
	data->mouse_center_x = SCRN_W / 2;
	data->mouse_center_y = SCRN_H / 2;
	data->mouse_dx = 0;
	data->mouse_sens = 0.0015;
	data->max_rot_frame = 0.06;
	data->mouse_ready = 0;
	data->direction.x = 0.0;
	data->direction.y = -1.0;
	data->cam.x = 0.66;
	data->cam.y = 0.0;
	data->pitch = 100;
	data->vmove = 0.3;
}
