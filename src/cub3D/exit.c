#include "../../include/cub3d.h"

int	exit_error(t_game *g, char *str)
{
	if (str)
	{
		write(STDOUT_FILENO, ERR_RED, ft_strlen(ERR_RED));
		write(STDOUT_FILENO, str, ft_strlen(str));
		write(STDOUT_FILENO, RESET, ft_strlen(RESET));
	}
	exit_game(g);
	return (EXIT_FAILURE);
}

void	free_assign_elems(t_game *g)
{
	if (g->rndr.tex.imgs[EA].path)
		free(g->rndr.tex.imgs[EA].path);
	if (g->rndr.tex.imgs[SO].path)
		free(g->rndr.tex.imgs[SO].path);
	if (g->rndr.tex.imgs[WE].path)
		free(g->rndr.tex.imgs[WE].path);
	if (g->rndr.tex.imgs[NO].path)
		free(g->rndr.tex.imgs[NO].path);
}

int	exit_game(t_game *g)
{
	printf("(exit_game)Burdasın --> : %d\n", __LINE__);
	if (g && g->rndr.mlx_ptr && g->rndr.win_ptr)
	{
		mlx_destroy_window(g->rndr.mlx_ptr, g->rndr.win_ptr);
		mlx_destroy_image(g->rndr.mlx_ptr, g->rndr.img.img_ptr);
		// mlx_destroy_display(g->rndr.mlx_ptr);
		free(g->rndr.mlx_ptr);
	}
	if (g->rndr.map.fd_cub > STDERR_FILENO)
		close(g->rndr.map.fd_cub);
	free_assign_elems(g);
	free_dbl_arry(g->rndr.map.map);
	exit(EXIT_FAILURE);
	return (0);
}

void	gnl_free(char *buffer, int fd)
{
	while (1)
	{
		if (buffer)
			free(buffer);
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		free(buffer);
		buffer = NULL;
	}
}
