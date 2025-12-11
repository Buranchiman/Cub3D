#####################################PUSH_SWAP#####################################

NAME	=	cub3d
NAME_BONUS	=	cub4d

#####################################SRCS########################################

PATH_SRCS	=	SRCS/

SRCS	+=	checkmap.c
SRCS	+=	checktexture.c
SRCS	+=	cleanup.c
SRCS	+=	data.c
SRCS	+=	dda.c
SRCS	+=	display.c
SRCS	+=	first_calcs.c
SRCS	+=	gate.c
SRCS	+=	minimap.c
SRCS	+=	mlx_hooks.c
SRCS	+=	parsing_utils.c
SRCS	+=	pixel_util.c
SRCS	+=	player.c
SRCS	+=	raycasting.c
SRCS	+=	render.c
SRCS	+=	sprites.c
SRCS	+=	utils.c
SRCS	+=	walls.c
SRCS	+=	main.c

BONUS	+=	checkmap.c
BONUS	+=	checktexture.c
BONUS	+=	cleanup.c
BONUS	+=	data.c
BONUS	+=	dda.c
BONUS	+=	display.c
BONUS	+=	first_calcs.c
BONUS	+=	gate.c
BONUS	+=	minimap.c
BONUS	+=	mlx_hooks.c
BONUS	+=	parsing_utils.c
BONUS	+=	pixel_util.c
BONUS	+=	player.c
BONUS	+=	raycasting.c
BONUS	+=	sprites.c
BONUS	+=	utils.c
BONUS	+=	walls.c
BONUS	+=	main_bonus.c
BONUS	+=	bonus_monsters.c
BONUS	+=	bonus_doors.c

vpath	%.c	$(PATH_SRCS)

PATH_SRCS_BONUS	=	BONUS/

SRCS_BONUS	=	$(BONUS)

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

$(NAME_BONUS):	$(LIBFT) $(MLX) $(OBJS_BONUS)
	$(CC)	$(CFLAGS)	$(OBJS_BONUS) -o	$(NAME_BONUS) $(INCLUDE)	$(LIBFT)	 $(MLX) $(MLX_FLAGS)

$(OBJS_BONUS):	$(PATH_OBJS_BONUS)/%.o:$(PATH_SRCS_BONUS)%.c Makefile
	mkdir	-p	$(PATH_OBJS_BONUS)
	$(CC)	$(CFLAGS) -D BONUS_BUILD	-c	$<	-o	$@	$(INCLUDE)

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
