#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "ray.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "get_next_line.h"
# include "libft.h"

#define ERR_RED "\033[31;4m"
#define RESET "\033[0m"

#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF
#define GREY_PIXEL 0x808080

#define WIN_WIDTH 1024
#define WIN_HEIGHT 1024

#define FLOOR 0
#define CEIL 1

enum tex_enum{
	NO,
	WE,
	SO,
	EA
};

/**
 * @brief image data struct
 * store all the stuff we need to work
 */
typedef struct	s_img
{
	char			*path;
	void			*img_ptr;
	char			*addr;
	int				bpp; /* bits per pixel */
	int				line_len;
	int				endian;
}	t_img;

typedef struct	s_tex
{
	float	x;
	float	y;
	float	offset;
	float	end_x;
	float	end_y;
	t_img	imgs[4];
}	t_tex;

typedef struct	s_map
{
	char	**map;
	char	*gnl_buffer;
	int		fd_cub;
	int		elem_count;
	int		player_x;
	int		player_y;
	int		res_width;
	int		res_height;
	int		range;
	int		tile_size;
	char	pov_char;
}	t_map;

typedef struct s_frame
{
	t_square	minimap_wall;
	t_square	minimap_background;
	int			units;
	char		player_dir;
}	t_frame;

typedef struct s_render
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*param;
	float		move_speed;
	int			f_rgb;
	int			c_rgb;
	int			res_width;
	int			res_height;
	t_circle	circle;
	t_line		line;
	t_img		img;
	t_frame		frame;
	t_map		map;
	t_tex		tex;
}	t_render;

typedef struct	s_ray
{
	char		**map;
	double		fov;
	double		camera_x;
	double		perp_wall_dist;
	double		wall_x;
	double		tex_step;
	double		tex_pos;
	double		row_distance;
	int			map_width;
	int			map_height;
	int			hit;
	int			side;
	int			tile_size;
	int			tex_x;
	int			tex_y;
	t_point		player;
	t_line		line;
	t_point		step;
	t_point		pos;
	t_point		in_map;
	t_point		res;
	t_point		plane;
	t_point		direction;
	t_point		ray_dir;
	t_point		delta_dist;
	t_point		side_dist;
	t_point		tex;
	t_render	render;
}	t_ray;

typedef struct	s_game
{
	t_render		rndr;
	t_ray			ray;
}	t_game;


//key process
int		key_hook(int key, t_game *g);

//draw process
void	draw(t_game *g);
void	img_pix_put(t_img *img, int x, int y, int color);
void	render_background(t_game *g);
void	draw_minimap(t_game *g);
void	raycaster(t_ray *r);

//initialize variables
int		initialize(t_game *g, char *cub);
//file process
void	file_parse(t_game	*g, char *cub);
int		open_cub(t_game *g, char *cub); 
int		get_texture_and_map(t_game *g);
void	assign_path_and_color(t_game *g, char *buffer);
void	get_player_pos(t_game *g);

//utils
int		print_dbl_arry(char **arr, char sep);
int		free_dbl_arry(char **arr);
int		dbl_array_size(char **arr);
int		create_trgb(int t, int r, int g, int b);
void	ft_array_join(t_game *g, char ***dst, char *src);
int		is_white_space(char c);
int		check_extension(char *file, char *extension);
int		get_longest_row(char **map);

//exit
int		exit_game(t_game *g);
int		exit_error(t_game *g, char *str);
void	free_assign_elems(t_game *g);
void	gnl_free(char *buffer, int fd);

//map_check
void	check_map(t_game *g);
void	check_top_and_bottom(t_game *g);

//draw utils
void	get_color(t_img *img, int x, int y, int *color);
void	put_color_to_img(t_img *img, int x, int y, int color);
int	find_wall_direction(t_game *g);


void	check_sin(t_game *g);
void	check_cos(t_game *g);

float to_radian(float angle);

void	init_direction(t_game *g, char start);

//texture
void	texture(t_ray *r, int x);


void	init_ray(t_game *g);
void	init_ray_number(t_game *g);
void	init_ray_struct(t_game *g);

void	line_draw(t_ray *r);
#endif