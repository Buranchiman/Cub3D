/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:09 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/04 17:01:58 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	verif_param(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("\x1b[38;5;196m[Error : Wrong number of arguments]\033[0m\n");
		exit(1);
	}

	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
	{
		printf("\x1b[38;5;196m[Error : File map is not .cub]\033[0m\n");
		exit(1);
	}
}

int	main(int arc, char **arv)
{
	t_data	data;
	int 	i;
	
	i = 0;
	verif_param(arc, arv);
	check_file_format(arv[1]);
	get_map(&data, arv[1]);
	while (data.map[i])
	{
		printf(1, "%s\n", data.map[i]);
		i++;
	}
	return (0);
}
