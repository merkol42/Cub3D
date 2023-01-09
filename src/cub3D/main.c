#include "../../include/cub3d.h"
#include <sys/time.h>

int	loop(t_game *g)
{
	mlx_clear_window(g->rndr.mlx_ptr, g->rndr.win_ptr);
	// if (!g->rndr.win_ptr)
	// 	mlx_loop_end(g->rndr.mlx_ptr);
	draw(g);
	mlx_put_image_to_window(g->rndr.mlx_ptr, g->rndr.win_ptr, g->rndr.img.img_ptr, 0, 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	g;

	if (ac < 2 || ac != 2)
		exit_error(NULL, "Too Few or Many Arguments!!\n");
	initialize(&g, *(++av));
	mlx_hook(g.rndr.win_ptr, 17, 0, exit_game, &g);
	mlx_hook(g.rndr.win_ptr, 2, 1, &key_hook, &g);
	mlx_key_hook(g.rndr.win_ptr, &key_hook, &g);
	// mlx_loop_hook(g.rndr.mlx_ptr, loop, &g);
	mlx_loop(g.rndr.mlx_ptr);
	return (0);
}
