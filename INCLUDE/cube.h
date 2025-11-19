/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:38:11 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/19 17:31:28 by manon            ###   ########.fr       */
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

# define NBR_TEXTURES 7
# define NBR_TEXTURES_BONUS 3

// PATH TEXTURES
# define GROUND_MINIMAP "TEXTURES/ground_mp.xpm"
# define WALL_MINIMAP "TEXTURES/wall_mp.xpm"
# define PLAYER_MINIMAP "TEXTURES/player_mp.xpm"
# define EAST "TEXTURES/east.xpm"
# define NORTH "TEXTURES/north.xpm"
# define SOUTH "TEXTURES/south.xpm"
# define WEST "TEXTURES/west.xpm"

// BONUS TEXTURES
# define MONSTER "TEXTURES/monsters.xpm"
# define DOOR_CLOSED "TEXTURES/door_close.xpm"
# define DOOR_OPEN "TEXTURES/door_open.xpm"

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
# define CLOSEST 0.1 //closest you can get to a wall

# define IMG_SIZE 64

typedef enum e_cardinal
{
	CARDNORTH,
	CARDSOUTH,
	CARDEAST,
	CARDWEST,
}			t_cardinal;

typedef struct s_keys {
	int left;
	int right;
	int w;
	int s;
	int a;
	int d;
}				t_keys;

typedef struct s_img {
	void	*img;      // MLX image handle
	char	*addr;     // pointer to pixel data
	int		bpp;      // bits per pixel (usually 32)
	int		line_len; // bytes per row
	int		endian;   // byte order flag (0 or 1)
} t_img;

typedef struct s_texture
{
	char		*path;
	int			height;
	int			width;
	t_img		*ptr;
	uint32_t	*pixels;
}				t_texture;

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_monsters
{
	t_point	pos;
	int		count;
	//int		alive;
}				t_monsters;

typedef struct s_doors
{
	t_point	pos;
	int		lock;
	//int 	count;
	char 	*enigma;
	char 	*soluce;
}				t_doors;

typedef struct s_data
{
	char			**map;
	char			*buffer;
	int				held_key;
	unsigned long	last_update;
	int				cardinal;
	t_texture		texture[NBR_TEXTURES];
	t_point			player_pos;
	t_point			cameraplane;
	t_point			direction;
	t_img			*mlx_img;
	t_keys			keys;
	double			lasttime;
	double			deltatime;
	void			*mlx_ptr;
	void			*win_ptr;
	//bonus
	t_texture		texture_bonus[NBR_TEXTURES_BONUS];
	/* bonus objects */
	t_monsters			*tab_monsters;
	 t_doors		*tab_doors;
	 int			doors_count;
}				t_data;

//utils.c
double	get_time(void);
int		is_all_space_n_ones(char *string);
void	ft_clean_exit(t_data *data, int option, char *msg);
size_t	ft_tablen(char **tab);
int 	quit_with_int(t_data *data);

//checktextures.c
int		import_texture(int index, int which, char *line);
void	take_texture_out(char ***map, int end);
int		get_textures(char *line);
int		read_textures(char ***map);

//checkmap.c
void	read_all_file(char *file_name, t_data *data);
int		get_player(char **map, int i, int j);
void	check_borders(t_data *data, char **map, int pcount);
void	check_map(t_data *data, char **map);
void	get_map(char *file_name);

//data.c
t_img	*init_img();
void	init_data(void);
t_data	*get_data(void);

//raycasting.c
int		raycasting(t_data *data);
int		render_frame(void *param);

//walls.c
int		vertical_walls(char *line);
int		leak_check(char **map, int x, int y);

//minimap.c
void	display_window(t_data *data);
void	display_minimap(t_data *data);
void	update_minimap(t_data *data);

//bonus_monsters.c
int		monster_count(t_data *data);
void	monster_init(t_data *data);
void	monsters_move(t_data *data);

//bonus_doors.c
void	init_enigma(t_data *data, int i);
void	doors_init(t_data *data);
int		open_door(t_data *data, int i);
int		door_is_locked_at(t_data *data, int tx, int ty);
int		door_index_at(t_data *data, int tx, int ty);

#endif
