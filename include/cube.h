/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:38:11 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/04 13:08:20 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "libft.h"

typedef struct s_data
{
	char			**map;
	char			*buffer;
	unsigned int	pcount;
}				t_data;

int		is_all_c(char *string, char c);
void	ft_clean_exit(t_data *data, int option, char *msg);
void	check_file_format(char *file);

void	read_all_file(char *file_name, t_data *data);
void	check_borders(t_data *data, char **map);
void	check_map(t_data *data, char **map);
void	get_map(t_data *data, char *file_name);


#endif
