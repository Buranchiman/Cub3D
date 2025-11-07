/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:09 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/05 16:52:57 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	verif_param(int argc, char **argv)
{
	if (argc != 2)
		printf("\x1b[38;5;196m[Error : Wrong number of arguments]\033[0m\n");
	else if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
		printf("\x1b[38;5;196m[Error : File map is not .cub]\033[0m\n");
}

int	main(int arc, char **arv)
{
	t_data	*data;
	int		i;

	i = 0;
	verif_param(arc, arv);
	check_file_format(arv[1]);
	get_map(arv[1]);
	data = get_data();
	i = 0;
	while (data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	ft_clean_exit(data, 0, NULL);
	return (0);
}
