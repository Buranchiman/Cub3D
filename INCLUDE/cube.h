/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:38:11 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/11 14:49:17 by wivallee         ###   ########.fr       */
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

# define NBR_TEXTURES 16

// PATH TEXTURES
# define GROUND_MINIMAP "TEXTURES/ground_map.xpm"
# define WALL_MINIMAP "TEXTURES/wall_map.xpm"
# define PLAYER_MINIMAP "TEXTURES/player_map.xpm"
# define EAST "TEXTURES/path_to_the_east_texture.xpm"
# define NORTH "TEXTURES/path_to_the_north_texture.xpm"
# define SOUTH "TEXTURES/path_to_the_south_texture.xpm"
# define WEST "TEXTURES/path_to_the_west_texture.xpm"
# define MONSTER "TEXTURES/monster.xpm"
# define MONSTER2 "TEXTURES/monster2.xpm"
# define DOOR_CLOSED "TEXTURES/door_closed.xpm"
# define DOOR_OPENED "TEXTURES/door_opened.xpm"
# define MONSTER_MAP "TEXTURES/monster_map.xpm"
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
# define CLOSEST 0.1

# define CEILING_COLOR 0xFF87CEEB
# define FLOOR_COLOR 0xFF444444

# define IMG_SIZE 64

# define MAX_GATES_PER_COLUMN 16

typedef enum e_cardinal
{
	CARDNORTH,
	CARDSOUTH,
	CARDEAST,
	CARDWEST,
}			t_cardinal;

typedef struct s_keys
{
	int	left;
	int	right;
	int	w;
	int	s;
	int	a;
	int	d;
	int	e;
}				t_keys;

typedef struct s_gate_layer
{
	double	dist;
	int		texx;
	int		locked;
}				t_gate_layer;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_tex
{
	char		*path;
	int			height;
	int			width;
	t_img		*ptr;
	uint32_t	*pixels;
}				t_tex;

typedef struct s_gate_ctx
{
	int		x;
	int		gi;
	double	dist;
	t_tex	*tex;
}	t_gate_ctx;

typedef struct s_spx
{
	int		stripe;
	int		texx;
	int		tex_idx;
}	t_spx;

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

typedef struct s_ray
{
	double	raydirx;
	double	raydiry;
	double	deltadistx;
	double	deltadisty;
	double	sidedistx;
	double	sidedisty;
	int		stepx;
	int		stepy;
	int		mapx;
	int		mapy;
	int		side;
	int		hit;
	double	perpwalldist;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		texx;
	int		texy;
	double	step;
	double	texpos;
	double	wallx;
	int		cardinal;
}	t_ray;

typedef struct s_data
{
	char			**map;
	char			*buffer;
	unsigned long	last_update;
	int				cardinal;
	t_tex			tex[NBR_TEXTURES];
	t_point			player_pos;
	t_point			cam;
	t_point			direction;
	t_img			*mlx_img;
	t_keys			keys;
	double			lasttime;
	unsigned long	door_time;
	unsigned long	monster_time;
	double			deltatime;
	void			*mlx;
	void			*win_ptr;
	t_monster		*tab_m;
	int				monster_count;
	t_doors			*tab_doors;
	int				doors_count;
	char			*sky_path;
	t_tex			sky;
	int				mouse_center_x;
	int				mouse_center_y;
	double			mouse_sens;
	int				mouse_ready;
	int				mouse_dx;
	double			max_rot_frame;
	t_gate_layer	gatelayers[SCRN_W][MAX_GATES_PER_COLUMN];
	int				gatecount[SCRN_W];
	double			pixeldepth[SCRN_H][SCRN_W];
	double			zbuffer[SCRN_W];
	int				pitch;
	double			spritex;
	double			spritey;
	double			inv;
	double			transfx;
	double			transfy;
	int				spritescreenx;
	double			vmove;
	int				vmovescreen;
	int				spriteh;
	int				drawstarty;
	int				drawendy;
	int				spritewidth;
	int				drawstartx;
	int				drawendx;
	int				pos;
	unsigned int	color;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
}				t_data;

//utils.c
int		doors_count(t_data *data, int x, int y);
double	get_time(void);
int		is_all_space_n_ones(char *string);
size_t	ft_tablen(char **tab);
int		quit_with_int(t_data *data);

//checktexs.c
int		import_tex(int index, int which, char *line);
void	take_tex_out(char ***map, int end);
int		get_texs(char *line);
int		read_texs(char ***map);

//checkmap.c
void	set_direction(char c, t_data *data);
void	read_all_file(char *file_name, t_data *data);
void	check_borders(t_data *data, char **map, int pcount);
void	check_map(t_data *data, char **map);
void	get_map(char *file_name);

//cleanup.c
void	take_tex_out(char ***map, int end);
void	free_img(t_img *img);
void	free_data(t_data *data);
void	ft_clean_exit(t_data *data, int option, char *msg);

//data.c
t_ray	*get_ray(void);
t_img	*init_img(void);
void	init_data(void);
t_data	*get_data(void);

//raycasting.c
int		raycasting(t_data *data);
int		render_frame(void *param);

//parsing_utils.c
int		vertical_walls(char *line);
void	leak_check(char **map, int x, int y);

//minimap.c
void	display_window(t_data *data);
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

//pixel_util.c
void	put_px(t_data *d, int x, int y, unsigned int argb);
int		fetch_tex(int x, int y);

//player.c
int		get_player(char **map, int i, int j);
void	mouse_rotation(t_data *d);
void	update_player(t_data *d);

//gate.c
void	assign_gate_value(int x, int gate_tex,
			double gatedist, int texx_gate);
void	handle_gates(t_data *d, t_ray *r);

//sprites.c
void	calc_sprite_draw_area(t_data *d);
void	handle_sprites(t_data *d, t_ray *r);

//dda.c
void	get_wallside(t_ray *r, t_data *d);
void	hit_wall(t_ray *r, t_data *d, int x);
void	perform_dda(t_ray *r, t_data *d, int x);

//walls.c
void	walls_final_calc(t_data *d, t_ray *r, double wallx);
void	draw_walls(t_data *d, t_ray *r, int x);

//first_calcs.c
void	first_calc(t_ray *r, t_data *d, int x);
void	step_calc(t_ray *r, t_data *d);
void	calc_wall_drawing_area(t_ray *r, t_data *d);

//mlx_hooks.c
int		mouse_move(int x, int y, t_data *d);
int		on_keydown(int keycode, void *param);
int		on_keyup(int keycode, void *param);

//render.c
void	door_to_close(t_data *data);
int		render_frame(void *param);

//main.c
int		mouse_move(int x, int y, t_data *d);

#endif
