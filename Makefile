#####################################PUSH_SWAP#####################################

NAME	=	cub3d
NAME_BONUS	=	cub4d

#####################################SRCS########################################

PATH_SRCS	=	SRCS/

SRCS	+=	checkmap.c
SRCS	+=	checktexture.c
SRCS	+=	data.c
SRCS	+=	utils.c
SRCS	+=	raycasting.c
SRCS	+=	walls.c
SRCS	+=	display.c
SRCS	+=	main.c
SRCS	+=	minimap.c
# SRCS	+=	mouse_rotation.c
# SRCS	+=	pixel_util.c
# SRCS	+=	player_update.c
# SRCS	+=	raycast_gates.c
# SRCS	+=	raycast_sprites.c
# SRCS	+=	raycast_tmp.c
# SRCS	+=	render_frame.c
SRCS	+=	bonus_monsters.c
SRCS	+=	bonus_doors.c

vpath	%.c	$(PATH_SRCS)

PATH_SRCS_BONUS	=	srcs_bonus/

SRCS_BONUS	+=	main_bonus.c

vpath	%.c	$(PATH_SRCS_BONUS)

###################################OBJS#########################################

PATH_OBJS	=	objs
OBJS	=	$(patsubst	%.c,	$(PATH_OBJS)/%.o,	$(SRCS))

PATH_OBJS_BONUS	=	objs_bonus
OBJS_BONUS	=	$(patsubst	%.c,	$(PATH_OBJS_BONUS)/%.o,	$(SRCS_BONUS))

################################COMPILATION####################################

INCLUDE	=	-Ilibft/includes	-IINCLUDE -g

LIBFT	=	libft/libft.a

MLX_PATH = minilibx-linux
MLX = $(MLX_PATH)/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz

CFLAGS	=	-Wall	-Wextra	-Werror

##################################RULES#######################################

all:		$(NAME)


$(NAME): $(LIBFT) $(MLX) $(OBJS) $(MAIN)
	$(CC)	$(CFLAGS) $(OBJS)	-o	$(NAME)	$(INCLUDE)	$(LIBFT)	$(MLX) $(MLX_FLAGS)

$(LIBFT):
	${MAKE}	-sC	libft

$(MLX):
	${MAKE} -sC $(MLX_PATH)

$(MAIN): srcs/main.c
	$(CC)	$(CFLAGS)	-c	$<	-o	$@	$(INCLUDE)

$(OBJS):	$(PATH_OBJS)/%.o:%.c Makefile
	mkdir	-p	$(PATH_OBJS)
	$(CC)	$(CFLAGS)	-c	$<	-o	$@	$(INCLUDE)

bonus:	$(NAME_BONUS)

$(NAME_BONUS):	$(OBJS)	$(OBJS_BONUS)
	$(CC)	$(CFLAGS)	$(OBJS)	$(OBJS_BONUS) -o	$(NAME_BONUS) $(INCLUDE)	$(LIBFT)	 $(MLX) $(MLX_FLAGS)

$(OBJS_BONUS):	$(PATH_OBJS_BONUS)/%.o:%.c Makefile
	mkdir	-p	$(PATH_OBJS_BONUS)
	$(CC)	$(CFLAGS)	-c	$<	-o	$@	$(INCLUDE)

clean:
	rm	-rf	$(PATH_OBJS)
	rm	-rf	$(PATH_OBJS_BONUS)

fclean:	clean
	rm	-rf	$(NAME)
	rm	-rf	$(NAME_BONUS)
	${MAKE}	fclean -sC	libft

re:	fclean
	${MAKE}

malloc_test: $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ ${OBJS} libft/libft.a -L. -lmallocator

.PHONY:	all	libft	clean	fclean	re
