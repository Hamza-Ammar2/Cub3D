#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define SIZE 64

# define get_index(x) ((int)(x / SIZE))

/* ************************************************************************** */
/*                              CONFIG / MACROS                              */
/* ************************************************************************** */

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define WIN_TITLE "cub3D"

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define NUM_RAYS 50

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
	int		x;
	int		y;
	double	angle;
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


typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_rect;

typedef struct s_vect
{
	int x;
	int y;
} t_vect;


/* ************************************************************************** */
/*                               PARSING                                    */
/* ************************************************************************** */

int		parse_scene(t_game *game, char *path);
int		parse_textures(t_game *game, char *line);
int		parse_colors(t_game *game, char *line);
int		parse_map(t_game *game, int fd);
int		validate_map(t_game *game);

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
/*                              DRAWING                                   */
/* ************************************************************************** */


void	draw_rect(t_game *game, t_rect rect, int color);
void	draw_line(t_game *game, t_vect p0, t_vect p1, int color);
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_map2D(t_game *game);
void	draw_rays2D(t_player *player, t_game *game);
void	get_map(char *file, t_game *game);
t_vect	get_ray_end(t_game *game, double ray_angle);


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
char	*get_next_line(int fd);
char	*find_char(char *s, char c, size_t len);
char	*append(char *s1, char *s2, size_t l1, size_t l2);
#endif
