/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:38:11 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/06 14:25:55 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
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

# define IMG_SIZE 64

typedef struct s_texture
{
	char    *path;
	void    *ptr;
}               t_texture;

typedef struct s_data
{
	char			**map;
	char			*buffer;
	t_texture       texture[6];
	//void			*ptr; //pointer to the image
	void			*mlx_ptr; //mlx pointer 
	void			*win_ptr; //window pointer
}               t_data;

int		is_all_c(char *string, char c);
void	ft_clean_exit(t_data *data, int option, char *msg);
void	check_file_format(char *file);
size_t	ft_tablen(char **tab);

int		import_texture(int index, int which, char *line);
void	take_texture_out(char ***map, int end);
int		get_textures(char *line);
int		read_textures(char ***map);

void	read_all_file(char *file_name, t_data *data);
void	check_borders(t_data *data, char **map, int pcount);
void	check_map(t_data *data, char **map);
void	get_map(char *file_name);

void	init_data(void);
t_data	*get_data(void);

void	display_window(t_data *data);
void	display_minimap(t_data *data);
void	update_minimap(t_data *data);
void	free_minimap(t_data *data);

#endif
