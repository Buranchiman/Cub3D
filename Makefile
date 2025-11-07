#####################################CUB3D#######################################

NAME	=	cub3d
NAME_BONUS	=	cub4d

#####################################SRCS########################################

PATH_SRCS	=	SRCS/

SRCS	+=	checkmap.c
SRCS	+=	checktexture.c
SRCS	+=	data.c
SRCS	+=	utils.c
SRCS	+=	walls.c
SRCS	+=	main.c
SRCS	+=	minimap.c
SRCS	+=	load_textures.c

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

INCLUDE	=	-Ilibft/includes	-IINCLUDE	-Iminilibx-linux

LIBFT	=	libft/libft.a

CFLAGS	=	-Wall	-Wextra	-Werror	-g

MLX_LIB	=	-Lminilibx-linux -lmlx -lXext -lX11 -lm

##################################RULES#######################################

all:		$(NAME)


$(NAME): $(LIBFT)	$(OBJS)	$(MAIN)
	$(CC)	$(CFLAGS) $(OBJS)	-o	$(NAME)	$(INCLUDE)	$(LIBFT) $(MLX_LIB)

$(LIBFT):
	${MAKE}	-sC	libft

$(MAIN): srcs/main.c
	$(CC)	$(CFLAGS)	-c	$<	-o	$@	$(INCLUDE)

$(OBJS):	$(PATH_OBJS)/%.o:%.c Makefile
	mkdir	-p	$(PATH_OBJS)
	$(CC)	$(CFLAGS)	-c	$<	-o	$@	$(INCLUDE)

bonus:	$(NAME_BONUS)

$(NAME_BONUS):	$(OBJS)	$(OBJS_BONUS)
	$(CC)	$(CFLAGS)	$(OBJS)	$(OBJS_BONUS) -o	$(NAME_BONUS) $(INCLUDE)	$(LIBFT) $(MLX_LIB)

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
