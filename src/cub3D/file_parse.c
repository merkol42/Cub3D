#include "../../include/cub3d.h"

int	get_texture_and_map(t_game *g)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		buffer = get_next_line(g->rndr.map.fd_cub);
		if (!buffer)
			break ;
		if (!ft_strncmp(buffer, "\n", 1) && ft_strlen(buffer) == 1)
		{
			free(buffer);
			continue ;
		}
		if (g->rndr.map.elem_count < 6)
			assign_path_and_color(g, buffer);
		else
			ft_array_join(g, &g->rndr.map.map, ft_strtrim(buffer, "\n"));
		free(buffer);
	}
	g->rndr.map.res_width = get_longest_row(g->rndr.map.map);
	g->rndr.map.res_height = dbl_array_size(g->rndr.map.map);
	g->rndr.map.range = WIN_WIDTH;
	g->rndr.move_speed= (g->rndr.map.tile_size / 2) / 5;
	return (0);
}

void	assign_color(t_game *gm, char *str, int flag)
{
	char	*second;
	int		r;
	int		g;
	int		b;

	second = ft_strchr(str, ',') + 1;
	r = ft_atoi(str);
	g = ft_atoi(second);
	b = ft_atoi(ft_strchr(second, ',') + 1);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
	{
		free(str);
		gnl_free(gm->rndr.map.gnl_buffer, gm->rndr.map.fd_cub);
		exit_error(gm, "Wrong Color Code!\n");
	}
	if (flag == FLOOR)
		gm->rndr.f_rgb = create_trgb(0, r, g, b);
	else if (flag == CEIL)
		gm->rndr.c_rgb = create_trgb(0, r, g, b);
	free(str);
}

void	assign_path_and_color(t_game *g, char *buffer)
{
	g->rndr.map.gnl_buffer = buffer;
	if (!ft_strncmp(buffer, "NO ", 3))
		g->rndr.tex.imgs[NO].path = ft_strtrim(&buffer[3], "\r\t\n");
	else if (!ft_strncmp(buffer, "SO ", 3))
		g->rndr.tex.imgs[SO].path = ft_strtrim(&buffer[3], "\r\t\n");
	else if (!ft_strncmp(buffer, "EA ", 3))
		g->rndr.tex.imgs[EA].path = ft_strtrim(&buffer[3], "\r\t\n");
	else if (!ft_strncmp(buffer, "WE ", 3))
		g->rndr.tex.imgs[WE].path = ft_strtrim(&buffer[3], "\r\t\n");
	else if (!ft_strncmp(buffer, "F ", 2))
		assign_color(g, ft_strtrim(&buffer[1], "\r\t "), FLOOR);
	else if (!ft_strncmp(buffer, "C ", 2))
		assign_color(g, ft_strtrim(&buffer[1], "\r\t "), CEIL);
	else
	{
		gnl_free(buffer, g->rndr.map.fd_cub);
		exit_error(g, "Missing game element in .cub file!\n");
	}
	g->rndr.map.elem_count++;
}

void	file_parse(t_game	*g, char *cub)
{
	if (!check_extension(cub, ".cub"))
		exit_error(g, "Bad Extension!!\n");
	open_cub(g, cub);
	get_texture_and_map(g);
	check_map(g);
}