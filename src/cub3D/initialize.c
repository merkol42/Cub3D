#include "../../include/cub3d.h"

void	init_null(t_game *g)
{
	g->rndr.mlx_ptr = NULL;
	g->rndr.win_ptr = NULL;
	g->rndr.map.map = NULL;
	g->rndr.tex.imgs[EA].path = NULL;
	g->rndr.tex.imgs[SO].path = NULL;
	g->rndr.tex.imgs[NO].path = NULL;
	g->rndr.tex.imgs[WE].path = NULL;
	g->rndr.map.gnl_buffer = NULL;
	g->rndr.map.elem_count = 0;
	g->rndr.map.fd_cub = -1;
	g->rndr.map.tile_size = 64;
	g->rndr.tex.imgs[EA].img_ptr = NULL;
	g->rndr.tex.imgs[SO].img_ptr = NULL;
	g->rndr.tex.imgs[NO].img_ptr = NULL;
	g->rndr.tex.imgs[WE].img_ptr = NULL;
	g->rndr.res_width = WIN_WIDTH;
	g->rndr.res_height = WIN_HEIGHT;
	g->rndr.move_speed = 0.1;
}

void	init_assets(t_game *g)
{
	int	x;
	int	y;

	g->rndr.tex.imgs[EA].img_ptr = mlx_xpm_file_to_image(g->rndr.mlx_ptr, g->rndr.tex.imgs[EA].path, &x, &y);
	g->rndr.tex.imgs[NO].img_ptr = mlx_xpm_file_to_image(g->rndr.mlx_ptr, g->rndr.tex.imgs[NO].path, &x, &y);
	g->rndr.tex.imgs[SO].img_ptr = mlx_xpm_file_to_image(g->rndr.mlx_ptr, g->rndr.tex.imgs[SO].path, &x, &y);
	g->rndr.tex.imgs[WE].img_ptr = mlx_xpm_file_to_image(g->rndr.mlx_ptr, g->rndr.tex.imgs[WE].path, &x, &y);

	g->rndr.tex.imgs[EA].addr = mlx_get_data_addr(g->rndr.tex.imgs[EA].img_ptr, &g->rndr.tex.imgs[EA].bpp, &g->rndr.tex.imgs[EA].line_len, &g->rndr.tex.imgs[EA].endian);
	g->rndr.tex.imgs[NO].addr = mlx_get_data_addr(g->rndr.tex.imgs[NO].img_ptr, &g->rndr.tex.imgs[NO].bpp, &g->rndr.tex.imgs[NO].line_len, &g->rndr.tex.imgs[NO].endian);
	g->rndr.tex.imgs[SO].addr = mlx_get_data_addr(g->rndr.tex.imgs[SO].img_ptr, &g->rndr.tex.imgs[SO].bpp, &g->rndr.tex.imgs[SO].line_len, &g->rndr.tex.imgs[SO].endian);
	g->rndr.tex.imgs[WE].addr = mlx_get_data_addr(g->rndr.tex.imgs[WE].img_ptr, &g->rndr.tex.imgs[WE].bpp, &g->rndr.tex.imgs[WE].line_len, &g->rndr.tex.imgs[WE].endian);
}

void	init_ray_number(t_game *g)
{
	g->ray.map = g->rndr.map.map;
	g->ray.map_height = dbl_array_size(g->ray.map) - 1;
	g->ray.map_width = ft_strlen(*g->ray.map) - 1;
	g->ray.fov = M_PI / 4; // 45
	g->ray.tile_size = 64;
	g->ray.hit = 0;
	g->ray.side = 0;
	g->ray.perp_wall_dist = 0;
	g->ray.wall_x = 0;
	g->ray.tex_x = 0;
	g->ray.tex_y = 0;
	g->ray.tex_pos = 0;
	g->ray.camera_x = 0;
	g->ray.row_distance = 0;
}

void	init_ray_struct(t_game *g)
{
	g->ray.res = assign_point(WIN_WIDTH, WIN_HEIGHT);
	g->ray.pos = assign_point(g->rndr.map.player_x + 0.5, g->rndr.map.player_y + 0.5);
	g->ray.in_map = assign_point(0, 0);
	g->ray.delta_dist = assign_point(0, 0);
	g->ray.side_dist = assign_point(0, 0);
	g->ray.step = assign_point(0, 0);
	g->ray.line = init_line(0, 0, 0, 0);
	g->ray.ray_dir = assign_point(0, 0);
	g->ray.tex = assign_point(0, 0);
}

void	init_ray(t_game *g)
{
	init_ray_number(g);
	get_player_pos(g);
	init_ray_struct(g);
	g->ray.render = g->rndr;
	draw(g);
}

void	init_mlx(t_game *g)
{
	g->rndr.mlx_ptr = mlx_init();
	g->rndr.win_ptr = mlx_new_window(g->rndr.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	g->rndr.img.img_ptr = mlx_new_image(g->rndr.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	g->rndr.img.addr = mlx_get_data_addr(g->rndr.img.img_ptr, &g->rndr.img.bpp, &g->rndr.img.line_len, &g->rndr.img.endian);
}

int	initialize(t_game *g, char *cub)
{
	init_null(g);
	file_parse(g, cub);
	init_mlx(g);
	init_assets(g);
	init_ray(g);
	return (0);
}
