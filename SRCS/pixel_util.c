/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:00:00 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/05 15:34:56 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	put_px(t_data *d, int x, int y, unsigned int argb)
{
	char	*p;

	if ((unsigned int)x >= (unsigned int)SCRN_W)
		return ;
	if ((unsigned int)y >= (unsigned int)SCRN_H)
		return ;
	p = d->mlx_img->addr + y * d->mlx_img->line_len;
	p += x * (d->mlx_img->bpp / 8);
	*(unsigned int *)p = argb;
}

int	fetch_tex(char c, int x, int y)
{
	t_data	*d;
	int		idx;

	d = get_data();
	if (c == 'D')
	{
		idx = door_index_at(d, x, y);
		if (idx >= 0 && d->tab_doors && d->tab_doors[idx].lock)
			return (13);
		else if (idx >= 0 && d->tab_doors && !d->tab_doors[idx].lock)
			return (14);
	}
	return (d->cardinal);
}
