/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/12 11:58:10 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/26 16:51:15 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <get_next_line.h>
# include <libft.h>
# include <stdio.h>

/*
**	DEFINES
*/
# define W		13
# define A		0
# define S		1
# define D		2
# define LEFT	123
# define RIGHT	124
# define ESC	53

# define MLX_SYNC_IMAGE_WRITABLE		1
# define MLX_SYNC_WIN_FLUSH_CMD			2
# define MLX_SYNC_WIN_CMD_COMPLETED		3

# define WHITE	0x00FFFFFF
# define BLACK	0x00000000
# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define YELLOW	0x00FFFF00
# define LIGHTGRAY	0x009E9F8C
# define DARKGRAY	0x007e7f70

/*
**	Structs for vectors of type double & integer
*/

typedef struct s_d2vec
{
	double	x;
	double	y;
}				t_d2vec;

typedef struct s_i2vec
{
	int	x;
	int	y;
}				t_i2vec;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_pp;
	int		len;
	int		endian;
}				t_img;

typedef struct s_tex
{
	char	*path;
	t_img	img;
	int		x;
	int		y;
	double	wall_x;
	double	step;
	double	pos;
	int		width;
	int		height;
}				t_tex;

typedef struct s_map
{
	char		**grid;
	char		**check;
	int			*x;
	int			y;
	char		spawn_char;
	t_d2vec		spawn_pos;
	t_d2vec		spawn_dir;
	t_d2vec		plane;
}				t_map;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_file
{
	const char	*path;
	char		*line;
	char		spawn_char;
}				t_file;

/*
**	RAYCASTING STRUCT
**	camera_x:	x-coordinate in camera space.
**	side_dist:	distance to next x- or y-side.
**	delta_dist:	distance from one x- or y-side to next.
**	perp_dist:	perpendicular distance to wall.
**	step:		what x- and -y direction to step in (+1 or -1).
**	side:		if horizontal (y/NS) wall or vertical (x/EW) wall is hit.
**	line_height: the height of the line corresponding to the ray.
**	line_start:	the y-coordinate to start drawing the line at.
**	line_end:	the y-coordinate to stop drawing the line at.
*/

typedef struct s_ray
{
	t_d2vec		plane;
	double		camera_x;
	t_i2vec		map;
	t_d2vec		dir;
	t_d2vec		side_dist;
	t_d2vec		delta_dist;
	double		perp_dist;
	t_i2vec		step;
	int			side;
	int			line_height;
	int			line_start;
	int			line_end;
	double		time;
	double		old_time;
}				t_ray;

/*
**	Time stores the time of the current frame, old_time stores
**	the time of the previous frame: difference between them determines
**	the speed player moves at (in order to keep speed constant no matter how
**	long the calculation takes).
**	ceiling:	ceiling colour.
**	floor:		floor colour.
*/

typedef struct s_data
{
	void		*mlx;
	void		*window;
	t_img		img;
	t_file		file;
	t_ray		ray;
	t_map		map;
	t_tex		tex[4];
	t_keys		keys;
	t_i2vec		res;
	t_d2vec		pos;
	t_d2vec		dir;
	t_d2vec		plane;
	double		move_speed;
	double		rot_speed;
	int			ceiling;
	int			floor;
}			t_data;

void		init_data(t_data *data);
void		complete_data(t_data *data);
void		complete_tex(t_data *data);
int			key_press(int keycode, t_data *data);
int			key_release(int keycode, t_data *data);

/*
**	Parsing functions.
*/
typedef int	(*t_id)(t_data *data, char *id);
int			parse_start(t_data *data);
int			parse_res(t_data *data, char *line);
int			parse_tex(t_data *data, char *line);
int			colour(t_data *data, char *line);
int			parse_colour(int *colour, char *line);
int			parse_map(int fd, t_data *data, int ret);
char		**copy_map(t_list *list, int size);
int			get_map_info(t_map *map);
int			get_spawn_info(t_map *map, int i);
void		set_spawn_dir(t_map *map);
int			validate_map(t_map *map, char **grid);
int			floodfill(int y, int x, t_map *map);
int			create_trgb(int t, int r, int g, int b);

/*
**	Moving functions.
*/

void		move_hooks(t_data *data);
void		move_up(t_data *data);
void		move_down(t_data *data);
void		move_left(t_data *data);
void		move_right(t_data *data);

/*
**	Raycasting functions.
*/

void		raycaster(t_data *data, int x);
void		calc_step_distance(t_d2vec pos, t_ray *ray);
void		differential_analysis(t_data *data);
void		calc_line(t_d2vec pos, t_i2vec res, t_ray *ray);
void		rotate_left(t_data *data);
void		rotate_right(t_data *data);
void		calc_texture(t_data *data, int i);
void		put_texture(t_data *data, int x);
int			get_colour(t_tex *tex);

/*
**	Drawing functions.
*/
void		put_pixel(int x, int y, int colour, t_img *img);
void		put_line(int x, t_ray *ray, int colour, t_img *img);
void		init_environment(t_data *data);

#endif