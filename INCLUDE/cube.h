/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:38:11 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/03 18:42:06 by manon            ###   ########.fr       */
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

# define NBR_TEXTURES 14

// PATH TEXTURES
# define GROUND_MINIMAP "TEXTURES/ground_map.xpm"
# define WALL_MINIMAP "TEXTURES/wall_map.xpm"
# define PLAYER_MINIMAP "TEXTURES/player_map.xpm"
# define EAST "TEXTURES/east.xpm"
# define NORTH "TEXTURES/north.xpm"
# define SOUTH "TEXTURES/south.xpm"
# define WEST "TEXTURES/west.xpm"
# define MONSTER "TEXTURES/monster.xpm"
# define MONSTER2 "TEXTURES/monster2.xpm"
# define DOOR_CLOSED "TEXTURES/door_closed.xpm"
# define DOOR_OPENED "TEXTURES/door_opened.xpm"
# define MONSTER_MAP "TEXTURES/monster_map.xpm"//to rename i think
# define DOOR_CLOSED_MAP "TEXTURES/door_closed_map.xpm"
# define DOOR_OPENED_MAP "TEXTURES/door_opened_map.xpm"

// KEYBOARD_MOVES
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_E 101
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

//	DIMENSIONS
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define SCRN_W 1900
# define SCRN_H 1060
# define CLOSEST 0.1 //closest you can get to a wall

# define IMG_SIZE 64

# define MAX_GATES_PER_COLUMN 16

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
	int e;
}				t_keys;

typedef struct s_gate_layer
{
	double	dist;   // distance from player to this gate slice
	int		texX;   // X coordinate on gate tex
	int		locked;
}				t_gate_layer;


typedef struct s_img {
	void	*img;      // MLX image handle
	char	*addr;     // pointer to pixel data
	int		bpp;      // bits per pixel (usually 32)
	int		line_len; // bytes per row
	int		endian;   // byte order flag (0 or 1)
} t_img;

typedef struct s_tex
{
	char		*path;
	int			height;
	int			width;
	t_img		*ptr;
	uint32_t	*pixels;
}				t_tex;

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_monster
{
	t_point		pos;
	double		dist;
}				t_monster;

typedef struct s_doors
{
	t_point	pos;
	int		lock;
	int		to_closed;
	char	*enigma;
	char	*soluce;
}				t_doors;

typedef struct s_data
{
	char			**map;
	char			*buffer;
	int				held_key;
	unsigned long	last_update;
	int				cardinal;
	t_tex		tex[NBR_TEXTURES];
	t_point			player_pos;
	t_point			cam;
	t_point			direction;
	t_img			*mlx_img;
	t_keys			keys;
	unsigned long	lasttime;
	unsigned long	door_time;
	unsigned long	monster_time;
	double			deltatime;
	void			*mlx_ptr;
	void			*win_ptr;
	t_monster		*tab_m;
	int				monster_count;
	t_doors			*tab_doors;
	int				doors_count;
	char			*sky_path;
	t_tex		sky;
	int				mouse_center_x;
	int				mouse_center_y;
	double			mouse_sens;     // radians per pixel
	int				mouse_ready;    // 0 until first center
	int				mouse_dx;        // accumulated horizontal delta (pixels) since last frame
	double			max_rot_frame;   // hard cap per frame in radians (e.g. 0.06 ≈ 3.4°)
	t_gate_layer	gateLayers[SCRN_W][MAX_GATES_PER_COLUMN];
	int				gateCount[SCRN_W];
	double			pixelDepth[SCRN_H][SCRN_W];
	double			zbuffer[SCRN_W];
}				t_data;

//utils.c
unsigned long	get_time(void);
int				is_all_space_n_ones(char *string);
void			ft_clean_exit(t_data *data, int option, char *msg);
size_t			ft_tablen(char **tab);
int				quit_with_int(t_data *data);

//checktexs.c
int		import_tex(int index, int which, char *line);
void	take_tex_out(char ***map, int end);
int		get_texs(char *line);
int		read_texs(char ***map);

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
void	leak_check(char **map, int x, int y);

//minimap.c
void	display_window(t_data *data, int i);
//void	display_window(t_data *data);
void	display_minimap(t_data *data, int x, int y);

//bonus_monsters.c
int		monster_count(t_data *data, int x, int y);
void	monster_init(t_data *data, int x, int y);
void	monsters_move(t_data *data);

//bonus_doors.c
void	init_enigma(t_data *data, int i);
void	doors_init(t_data *data, int x, int y);
int		open_door(t_data *data, int i);
int		door_is_locked_at(t_data *data, int tx, int ty);
int		door_index_at(t_data *data, int tx, int ty);

//main.c
int		mouse_move(int x, int y, t_data *d);

// /* pixel / tex utils */
// void	put_px(t_data *d, int x, int y, unsigned int argb);
// int		fetch_tex(char c, int x, int y);

// /* player / raycasting */
// void	update_player(t_data *d);
// int		raycasting(t_data *data);

// /* mouse */
// void	mouse_rotation(t_data *data);

// //draw_gate
// void	draw_gates(t_data *data, int pitch, int h);

// //draw_sprites
// void	draw_sprites(t_data *d, int pitch);

#endif
