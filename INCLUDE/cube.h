/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:38:11 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/04 15:48:13 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <sys/time.h>

// KEYBOARD_MOVES
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363


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
