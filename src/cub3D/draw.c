#include "../../include/cub3d.h"

// void fill_pixels(t_game *game, int color, int x, int y)
// {
//     *(int *)(game->image.addr + (y * game->image.size_len + x * game->image.bpp / 8)) = color;
// }

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

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

	x = -1;
	y = -1;
	while (++x < 8)
	{
		y = -1;
		while (++y < 8)
			img_pix_put(&g->rndr.img, g->rndr.map.player_x + x, g->rndr.map.player_y + y, 0xFF);
	}
}

//draw square with outline for minimap
void	draw_square(t_game *g, int px, int py, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 9)
	{
		x = -1;
		while (++x < 9)
			img_pix_put(&g->rndr.img, x + px, y + py, color);
	}
}

void draw_minimap(t_game *g) // make editable later
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (g->rndr.map.map[j])
	{
		i = 0;
		while (g->rndr.map.map[j][i])
		{
			if (g->rndr.map.map[j][i] == '1')
				draw_square(g, (i * 10), (j * 10), 0xfff000);
			// else
			//	draw_square(g, (i * 10), (j * 10), 0xffffff);
			i++;
		}
		j++;
	}
}

void	aim(t_game *g)
{
	t_line	line;

	line.start_x = WIN_WIDTH / 2;
	line.start_y = WIN_HEIGHT / 2 - 10;
	line.end_x = WIN_WIDTH / 2;
	line.end_y = WIN_HEIGHT / 2;
	line.delta.x = line.end_x - line.start_x  < 0 ? -1 : 1;
	line.delta.y = line.end_y - line.start_y  < 0 ? -1 : 1;
	g->ray.line = line;
	line_draw(&g->ray);
}

void	draw(t_game *g)
{
	// mlx_clear_window(g->rndr.mlx_ptr, g->rndr.win_ptr);
	render_background(g);
	// aim(g);
	raycaster(&g->ray);
	// draw_minimap(g);
	// draw_player(g);
	// mlx_put_image_to_window(g->rndr.mlx_ptr, g->rndr.win_ptr, g->rndr.img.img_ptr, 0, 0);
}