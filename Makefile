# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/27 11:29:07 by nsterk        #+#    #+#                  #
#    Updated: 2021/04/01 16:48:13 by nsterk        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d
CC			=	gcc
W_FLAGS		=	-Wall -Werror -Wextra -std=c89 -Iinc
MLX_FLAGS	=	-framework OpenGL -framework Appkit -Imlx -g

# MLX_PATH	=	./mlx/
LIBFT_PATH	=	./srcs/libft/
GNL_PATH	=	./srcs/gnl/
PARSE_PATH	=	./srcs/parsing/
CUB3D_PATH	=	./srcs/

LIBFT_C		=	ft_atoi.c ft_bzero.c ft_calloc.c \
				ft_free_array.c \
				ft_isalnum.c ft_isalpha.c ft_isdigit.c \
				ft_lstnew.c ft_lstlast.c ft_stradd_back.c \
				ft_skipspace.c \
				ft_strchr.c ft_strcpy.c ft_strlcpy.c \
				ft_strdup.c \
				ft_strlen.c ft_substr.c \
				ft_strtrim.c ft_split.c
GNL_C		=	get_next_line.c get_next_line_utils.c
PARSE_C		=	parser.c parse_map.c parse_colour_res.c
CUB3D_C		=	main.c init.c raycaster.c draw.c

LIBFT_SRCS	=	$(LIBFT_C:%=$(LIBFT_PATH)%)
GNL_SRCS	=	$(GNL_C:%=$(GNL_PATH)%)
PARSE_SRCS	=	$(PARSE_C:%=$(PARSE_PATH)%)
CUB3D_SRCS	=	$(CUB3D_C:%=$(CUB3D_PATH)%)

# place main.c in srcs folder
SRCS		= 	$(LIBFT_SRCS) $(GNL_SRCS) \
				$(PARSE_SRCS) $(CUB3D_SRCS)			
OBJS		=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	# make -C ./mlx
	# cp ./mlx/libmlx.dylib .
	$(CC) $(W_FLAGS) $(MLX_FLAGS) $(SRCS) libmlx.dylib -o $(NAME)

clean:
	# make clean -C ./mlx
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: all clean
