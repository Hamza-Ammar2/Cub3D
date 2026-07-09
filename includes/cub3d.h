#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <../minilibx-linux/mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

/* ************************************************************************** */
/*                              CONFIG / MACROS                              */
/* ************************************************************************** */

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define WIN_TITLE "cub3D"

# define BUFFER_SIZE 4096

# define SIZE 64
# define get_index(x) ((int)(x / SIZE))

# define MOVE_SPEED 0.02
# define ROT_SPEED 0.03
# define NUM_RAYS WIN_WIDTH

/* Field of view scaling for the camera plane (0.66 ~= 66 degrees FOV). */
# define FOV_SCALE 0.66
# define PI 3.14159265358979323846

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

typedef struct s_timing
{
	double	last_frame;
	double	target_fps;
}	t_timing;

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

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_rect;

typedef struct s_vect
{
	double	x;
	double	y;
}	t_vect;

/* Parsed scene configuration coming from the .cub file. */
typedef struct s_config
{
	char	*tex_path[4];
	int		floor_color;
	int		ceiling_color;
	int		floor_set;
	int		ceiling_set;
	char	**map;
	int		map_width;
	int		map_height;
	double	start_x;
	double	start_y;
	char	start_dir;
}	t_config;

/* Player position and facing angle (pixel coords for movement/raycast). */
typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
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
	t_timing	timing;
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

/* Working state for the map-closure flood fill (see validate_map). */
typedef struct s_flood
{
	char	**map;
	int		width;
	int		height;
	int		leaked;
}	t_flood;

/* ************************************************************************** */
/*                               PARSING                                    */
/* ************************************************************************** */

int		parse_scene(t_game *game, char *path);
int		check_extension(char *path);
int		handle_line(t_game *game, char *line, int *map_started,
			t_list **map_lines);
int		all_config_set(t_game *game);
int		parse_textures(t_game *game, char *line);
int		parse_colors(t_game *game, char *line);
int		parse_color_fields(char **color_fields, int *is_floor);
int		parse_rgb(char *str);
int		store_color(t_game *game, int is_floor, int rgb);
int		is_valid_number(char *str);
int		build_map(t_game *game, t_list *map_lines);
int		validate_map(t_game *game);
int		check_closed(t_game *game);
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
void	draw_column(t_game *game, t_rect uv, int x, int line_h);
t_vect	get_end(t_game *game, double ray_angle);
void	draw_img(t_img *frame, t_img *src, t_rect src_rect, t_rect dst);

/* ************************************************************************** */
/*                              DRAWING                                     */
/* ************************************************************************** */

void	draw_rect(t_game *game, t_rect rect, int color);
void	draw_line(t_game *game, t_vect p0, t_vect p1, int color);
void	draw_map2d(t_game *game);
void	draw_rays2d(t_player *player, t_game *game);

/* ************************************************************************** */
/*                            PLAYER / EVENTS                               */
/* ************************************************************************** */

int		handle_keypress(int key, t_game *game);
int		handle_keyrelease(int key, t_game *game);
int		handle_close(t_game *game);
int		update_player(t_game *game);
int		key_it(int key, t_game *game);
int		handle_rotation(int key, t_game *game);

/* ************************************************************************** */
/*                                UTILS                                     */
/* ************************************************************************** */

int		error_exit(char *msg);
void	free_game(t_game *game);
void	free_split(char **arr);
void	put_pixel(t_img *img, int x, int y, int color);
double	get_distance(t_vect start, t_vect end);
int		game_loop(void *param);
double	get_time_ms(void);
void	clear_image(t_img *img);
int		load_image(t_game *game, t_img *img, char *path);

/* ************************************************************************** */
/*                            GET_NEXT_LINE                                */
/* ************************************************************************** */

char	*get_next_line(int fd);
char	*append(char *s1, char *s2, size_t l1, size_t l2);
char	*find_char(char *s, char c, size_t len);

#endif
