# **************************************************************************** #
#                                   cub3D                                     #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# ---------------------------------------------------------------------------- #
#   Directories                                                                 #
# ---------------------------------------------------------------------------- #
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

# ---------------------------------------------------------------------------- #
#   Sources                                                                     #
# ---------------------------------------------------------------------------- #
SRCS		= \
	src/main.c \
	src/parsing/parse_scene.c \
	src/parsing/parse_textures.c \
	src/parsing/parse_colors.c \
	src/parsing/parse_colors_rgb.c \
	src/parsing/parse_colors_helpers.c \
	src/parsing/parse_map.c \
	src/parsing/validate_map.c \
	src/parsing/flood_fill.c \
	src/parsing/parse_utils.c \
	src/parsing/handle_line.c \
	src/init/init_game.c \
	src/raycasting/raycaster.c \
	src/raycasting/cast_horizontal.c \
	src/raycasting/cast_vertical.c \
	src/raycasting/cast2D.c \
	src/raycasting/draw.c \
	src/raycasting/render.c \
	src/player/movement.c \
	src/events/hooks.c \
	src/utils/errors.c \
	src/utils/game_loop.c \
	src/utils/handle_keys.c \
	src/utils/vect_utils.c \
	src/utils/free.c \
	src/utils/get_next_line.c \
	src/utils/get_next_line_utils.c \
	src/utils/img_utils.c

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ---------------------------------------------------------------------------- #
#   Libraries                                                                   #
# ---------------------------------------------------------------------------- #
LIBFT		= $(LIBFT_DIR)/libft.a
# Linux (X11) linking against a SYSTEM-installed MiniLibX (headers in
# /usr/local/include, libmlx.a in /usr/local/lib). The local minilibx/mlx.h
# wrapper uses #include_next to reach the system header.
#MLX_FLAGS	= -L/usr/local/lib -lmlx -lXext -lX11 -lm
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# ---------------------------------------------------------------------------- #
#   Rules                                                                       #
# ---------------------------------------------------------------------------- #
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) bonus

bonus: all

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
