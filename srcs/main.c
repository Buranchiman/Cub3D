/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:09 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/04 13:14:46 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int arc, char **arv)
{
	t_data	data;

	if (arc != 2)
	{
		ft_printf(1, "Incorrect number of params\n");
		return (0);
	}
	check_file_format(arv[1]);
	get_map(&data, arv[1]);
	int i = 0;
	while (data.map[i])
	{
		ft_printf(1, "%s\n", data.map[i]);
		i++;
	}
	return (0);
}
