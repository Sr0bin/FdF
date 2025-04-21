# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 20:33:05 by rorollin          #+#    #+#              #
#    Updated: 2025/04/21 00:47:47 by rorollin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

#SOURCES######################

SOURCES_DIR = src

SOURCES_NAME = main.c init.c

SOURCES_GRAPHIC = draw.c graphic.c line.c

SOURCES_GEOMETRY = edge.c geometry.c projection.c vertex.c 

SOURCES_MLX = hook.c mlx_utils.c 

SOURCES_PARSING = array_utils.c parsing.c

SOURCES_DEBUG = matrix_test.c graphic_test.c debug.c camera.c

SOURCES = $(addprefix $(SOURCES_DIR)/,\
		  $(SOURCES_NAME)\
		  $(addprefix graphic/, $(SOURCES_GRAPHIC))\
		  $(addprefix geometry/, $(SOURCES_GEOMETRY))\
		  $(addprefix mlx/, $(SOURCES_MLX))\
		  $(addprefix parsing/, $(SOURCES_PARSING))\
		  )
		  # $(addprefix .test/, $(SOURCES_DEBUG))\
		  


#OBJECTS#######################

OBJ_DIR = obj

OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

#DEPS##########################

DEPS = $(SOURCES:%.c=$(OBJ_DIR)/%.d)

#INCLUDES#######################

HEADERS_DIR = include/ libft/include/ minilibx/

INCLUDES = $(addprefix -I , $(HEADERS_DIR))

#LIBFT########################

LIBFT = libft

LIBFT_PATH = $(LIBFT)/$(LIBFT).a
#MINILIBX#####################

MINILIBX = libmlx.a

MINILIBX_PATH = minilibx/$(MINILIBX)
#COMPILER#####################

COMPILER = cc

CFLAGS_DEBUG = -Wall -Wextra -Werror -MMD -MP -ggdb3 -Wshadow -Wconversion -Wsign-conversion -Wmissing-prototypes \
-Wformat=2 -Wformat-security -Wnull-dereference -Wstack-protector -Wfloat-equal -Wpointer-arith \
-Wcast-align -Wundef -Wbad-function-cast -Wstrict-overflow=4 -Wdouble-promotion -Walloca -Wvla \
-Wwrite-strings -Wuninitialized -fno-delete-null-pointer-checks -fno-omit-frame-pointer -std=c11

CFLAGS_PROD = -Wall -Wextra -Werror -MMD -MP -ggdb3 -O3

CFLAGS = $(CFLAGS_PROD)

export CFLAGS

all: git make_libft make_minilibx $(NAME)

$(NAME):  $(OBJECTS) $(LIBFT_PATH) $(MINILIBX_PATH)
	$(COMPILER) $(CFLAGS) -lc -lm -lXext -lX11 $(INCLUDES) $^ -o $@
	@echo "$(NAME) built succesfully."


$(OBJ_DIR)/%.o: %.c 
	mkdir -p $(dir $@)
	$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS)

git: 
	@git submodule update --init --remote --recursive

make_libft:
	$(MAKE) -C $(LIBFT)
	
make_minilibx:
	@$(MAKE) -s -C minilibx

clean:
	@$(MAKE) -s -C $(LIBFT) clean
	@rm -rf $(OBJ_DIR)
	@rm -rf .cache/
	@rm -f .bonus
	@echo "Cleaned !"

fclean:
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) clean
	@rm -f $(NAME)
	@echo "Fcleaned !"

re:	
	$(MAKE) fclean 
	$(MAKE) all


.PHONY: all clean fclean re make_libft make_minilibx git
