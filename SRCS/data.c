/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:42:04 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/12 19:05:05 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	init_data(void)
{
	t_data	*data;
	//int		i;

	//i = 0;
	data = get_data();
	//data->buffer = NULL;
	//data->map = NULL;
	//data->mlx_ptr = NULL;
	//data->win_ptr = NULL;	
	ft_bzero(data, sizeof(t_data));
	//while (i < NBR_TEXTURES)
	//{
	//	data->texture[i].path = NULL;
	//	data->texture[i].ptr = NULL;
	//	i++;
	//}
}
