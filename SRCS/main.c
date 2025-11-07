/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:07:09 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/07 16:23:27 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

void	verif_param(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Wrong number of arguments");
		exit(1);
	}

	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
	{
		printf("File map is not .cub");
		exit(1);
	}
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
		ft_printf(1, "%s\n", data->map[i]);
		i++;
	}
	display_window(data);
	sleep(2);
	display_minimap(data);
	//update_minimap(&data);
	ft_clean_exit(data, 0, NULL);
	return (0);
}
