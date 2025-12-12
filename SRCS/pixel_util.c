/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:00:00 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/12 14:31:13 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	put_px(t_data *d, int x, int y, unsigned int argb)
{
	char	*p;

	if ((unsigned)x >= (unsigned)SCRN_W
		|| (unsigned)y >= (unsigned)SCRN_H)
		return ;
	p = d->mlx_img->addr + y * d->mlx_img->line_len + x * (d->mlx_img->bpp / 8);
	*(unsigned int *)p = argb;
}
