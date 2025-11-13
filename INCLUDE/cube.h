/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillichien <chillichien@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:38:11 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/12 14:22:21 by chillichien      ###   ########.fr       */
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

// PATH TEXTURES
# define GROUND_MINIMAP "../TEXTURES/ground.xpm"
# define WALL_MINIMAP "../TEXTURES/wall_mp.xpm"
# define PLAYER_MINIMAP "../TEXTURES/player_mp.xpm"

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

//	DIMENSIONS
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define SCREENWIDTH 1900
# define SCREENHEIGHT 1060

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

# define IMG_SIZE 64

typedef struct s_texture
{
	char	*path;
	int		height;
	int		width;
	void	*ptr;
}				t_texture;

typedef struct s_img {
    void *img;      // MLX image handle
    char *addr;     // pointer to pixel data
    int   bpp;      // bits per pixel (usually 32)
    int   line_len; // bytes per row
    int   endian;   // byte order flag (0 or 1)
} t_img;

typedef struct s_data
{
	char			**map;
	char			*buffer;
	t_texture		texture[9]; //t_texture		texture[6]; 6 map + 3 minimap + ? bonus_map
	t_point			player_pos;
	t_point			cameraplane;
	t_point			direction;
	void			*mlx_ptr; //mlx pointer
	void			*win_ptr; //window pointer
	s_img			*mlx_img; //img dans laquelle on va put_px
}				t_data;

//utils.c
//void	empty_struct_array(void *array, int size, size_t elem_size, void (*del)(void *));
int		is_all_space_n_ones(char *string);
void	ft_clean_exit(t_data *data, int option, char *msg);
//void	check_file_format(char *file);
size_t	ft_tablen(char **tab);
int 	quit_with_int(t_data *data);

//checktextures.c
int		import_texture(int index, int which, char *line);
void	take_texture_out(char ***map, int end);
int		get_textures(char *line);
int		read_textures(char ***map);

//checkmap.c
void	read_all_file(char *file_name, t_data *data);
void	check_borders(t_data *data, char **map, int pcount);
void	check_map(t_data *data, char **map);
void	get_map(char *file_name);

//data.c
void	init_data(void);
t_data	*get_data(void);

//raycasting.c
int		raycasting(t_data *data);
//walls.c
int		vertical_walls(char *line);
int		leak_check(char **map, int x, int y);

//minimap.c
void	display_window(t_data *data);
void	display_minimap(t_data *data);
void	update_minimap(t_data *data);

//input.c
int		key_hook(int keycode, t_data *data);

#endif
