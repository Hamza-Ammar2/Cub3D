#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* ************************************************************************** */
/*                              CONFIG / MACROS                              */
/* ************************************************************************** */

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define WIN_TITLE "cub3D"

# define BUFFER_SIZE 4096

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

/* Field of view scaling for the camera plane (0.66 ~= 66 degrees FOV). */
# define FOV_SCALE 0.66

/* Keycodes (Linux / X11). Adjust if building on macOS. */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* Cardinal directions, used to index the wall texture array. */
enum e_dir
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

/* ************************************************************************** */
/*                                 STRUCTS                                  */
/* ************************************************************************** */

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* Parsed scene configuration coming from the .cub file. */
typedef struct s_config
{
	char	*tex_path[4];
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		map_width;
	int		map_height;
	double	start_x;
	double	start_y;
	char	start_dir;
}	t_config;

/* Player position, facing vector and camera plane. */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/* Per-key held state for smooth movement. */
typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

/* Master game state passed around everywhere. */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_img		textures[4];
	t_config	config;
	t_player	player;
	t_keys		keys;
}	t_game;

/*
** Transient state used ONLY while parsing the .cub file. It is created in
** parse_scene(), threaded through the parsing helpers, and discarded once the
** finished data has been committed to t_game.config. Keeps t_game clean of
** fields that have no meaning after parsing is done.
*/
typedef struct s_parser
{
	t_game	*game;
	int		fd;
	int		line_no;
	int		in_map;
	int		seen;
	t_list	*map_lines;
}	t_parser;

/* ************************************************************************** */
/*                               PARSING                                    */
/* ************************************************************************** */

int		parse_scene(t_game *game, char *path);
int		parse_textures(t_game *game, char *line);
int		parse_colors(t_game *game, char *line);
int		parse_map(t_game *game, int fd);
int		validate_map(t_game *game);
int		is_empty_line(char *line);
char	*strip_newline(char *line);
int		count_words(char **split);

/* ************************************************************************** */
/*                                 INIT                                     */
/* ************************************************************************** */

int		init_game(t_game *game);
int		init_player(t_game *game);
int		load_textures(t_game *game);

/* ************************************************************************** */
/*                              RAYCASTING                                  */
/* ************************************************************************** */

int		render_frame(t_game *game);
void	cast_rays(t_game *game);
void	draw_column(t_game *game, int x);

/* ************************************************************************** */
/*                            PLAYER / EVENTS                               */
/* ************************************************************************** */

int		handle_keypress(int key, t_game *game);
int		handle_keyrelease(int key, t_game *game);
int		handle_close(t_game *game);
int		update_player(t_game *game);

/* ************************************************************************** */
/*                                UTILS                                     */
/* ************************************************************************** */

int		error_exit(char *msg);
void	free_game(t_game *game);
void	free_split(char **arr);
void	put_pixel(t_img *img, int x, int y, int color);

/* ************************************************************************** */
/*                            GET_NEXT_LINE                                */
/* ************************************************************************** */

char	*get_next_line(int fd);
char	*append(char *s1, char *s2, size_t l1, size_t l2);
char	*find_char(char *s, char c, size_t len);

#endif
