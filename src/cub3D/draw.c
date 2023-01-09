#include "../../include/cub3d.h"

void	render_background(t_game *g)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	color = g->rndr.f_rgb;
	while (i < WIN_HEIGHT)
	{
		j = -1;
		if (i == WIN_HEIGHT / 2)
			color = g->rndr.c_rgb;
		while (++j < WIN_WIDTH)
			img_pix_put(&g->rndr.img, j, i, color);
		++i;
	}
}

void	draw_player(t_game *g)
{
	int	x;
	int	y;
	int	poffset_x;
	int	poffset_y;

	x = -1;
	y = -1;
	poffset_x = g->ray.player.x;
	poffset_y = g->ray.player.y;
	if (g->ray.player.y > 128)
		poffset_y -= g->ray.player.y - 128;
	if (g->ray.player.x > 128)
		poffset_x -= g->ray.player.x - 128;
	while (++x < 10)
	{
		y = -1;
		while (++y < 10)
			img_pix_put(&g->rndr.img, poffset_x + x, poffset_y + y, 0xFF);
	}
}

void	draw_map_x(t_game *g, int mapx, int mapy, int c)
{
	int	z;

	z = 0;
	while (z < 256)
	{
		if (mapy / 64 < g->ray.map_height && mapx / 64 < g->ray.map_width
			&& g->ray.map[(int)(mapy / 64)][(int)(mapx / 64)] == '1')
			img_pix_put(&g->rndr.img, z, c, 0x00ffff);
		if (mapy / 64 < g->ray.map_height && mapx / 64 < g->ray.map_width
			&& !(mapy % 32))
			img_pix_put(&g->rndr.img, z, c, 0);
		if (mapy / 64 < g->ray.map_height && mapx / 64 < g->ray.map_width
			&& !(mapx % 32))
			img_pix_put(&g->rndr.img, z, c, 0);
		mapx++;
		z++;
	}
}

void	draw_minimap(t_game *g)
{
	int	mapx;
	int	mapy;
	int	c;

	mapx = 0;
	mapy = 0;
	c = 0;
	if (g->ray.player.y > 128)
		mapy = g->ray.player.y - 128;
	while (c < 256)
	{
		if (g->ray.player.x > 128)
			mapx = g->ray.player.x - 128;
		else
			mapx = 0;
		draw_map_x(g, mapx, mapy, c);
		mapy++;
		c++;
	}
}

void	draw(t_game *g)
{
	mlx_clear_window(g->rndr.mlx_ptr, g->rndr.win_ptr);
	render_background(g);
	raycaster(&g->ray);
	draw_minimap(g);
	draw_player(g);
	mlx_put_image_to_window(g->rndr.mlx_ptr, g->rndr.win_ptr,
		g->rndr.img.img_ptr, 0, 0);
}
