#include "../../include/cub3d.h"

void	turn_right(t_game *g)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->ray.direction.x;
	old_plane_x = g->ray.plane.x;
	g->ray.direction.x = old_dir_x * cos(TURN_SPEED) - g->ray.direction.y * sin(TURN_SPEED);
	g->ray.direction.y = old_dir_x * sin(TURN_SPEED) + g->ray.direction.y * cos(TURN_SPEED);
	g->ray.plane.x = old_plane_x * cos(TURN_SPEED) - g->ray.plane.y * sin(TURN_SPEED);
	g->ray.plane.y = old_plane_x * sin(TURN_SPEED) + g->ray.plane.y * cos(TURN_SPEED);
}

void	turn_left(t_game *g)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->ray.direction.x;
	old_plane_x = g->ray.plane.x;
	g->ray.direction.x = old_dir_x * cos(-TURN_SPEED) - g->ray.direction.y * sin(-TURN_SPEED);
	g->ray.direction.y = old_dir_x * sin(-TURN_SPEED) + g->ray.direction.y * cos(-TURN_SPEED);
	g->ray.plane.x = old_plane_x * cos(-TURN_SPEED) - g->ray.plane.y * sin(-TURN_SPEED);
	g->ray.plane.y = old_plane_x * sin(-TURN_SPEED) + g->ray.plane.y * cos(-TURN_SPEED);
}

void	turn_angle(t_game *g, int dir)
{
	if (dir == 124)
		turn_right(g);
	if (dir == 123)
		turn_left(g);
}

void	back_and_forward(t_game *g, int dir)
{
	int	x;
	int	y;

	x = (int)(g->ray.pos.x + g->ray.direction.x * g->rndr.move_speed);
	y = (int)(g->ray.pos.y + g->ray.direction.y * g->rndr.move_speed);
	if (dir == 13)
	{
		if (g->ray.map[(int)g->ray.pos.y][x] == '0')
			g->ray.pos.x += g->ray.direction.x * g->rndr.move_speed;
		if (g->ray.map[y][(int)g->ray.pos.x] == '0')
			g->ray.pos.y += g->ray.direction.y * g->rndr.move_speed;
		return ;
	}
	x = (int)(g->ray.pos.x - g->ray.direction.x * g->rndr.move_speed);
	y = (int)(g->ray.pos.y - g->ray.direction.y * g->rndr.move_speed);
	if (g->ray.map[(int)g->ray.pos.y][x] == '0')
		g->ray.pos.x -= g->ray.direction.x * g->rndr.move_speed;
	if (g->ray.map[y][(int)g->ray.pos.x] == '0')
		g->ray.pos.y -= g->ray.direction.y * g->rndr.move_speed;
}

void	left_and_right(t_game *g, int dir)
{
	int	x;
	int	y;

	x = (int)(g->ray.pos.x + g->ray.direction.y * g->rndr.move_speed);
	y = (int)(g->ray.pos.y - g->ray.direction.x * g->rndr.move_speed);
	if (dir == 2)
	{
		if (g->ray.map[(int)g->ray.pos.y][x] == '0')
			g->ray.pos.x += g->ray.direction.y * g->rndr.move_speed;
		if (g->ray.map[y][(int)g->ray.pos.x] == '0')
			g->ray.pos.y -= g->ray.direction.x * g->rndr.move_speed;
		return ;
	}
	x = (int)(g->ray.pos.x - g->ray.direction.y * g->rndr.move_speed);
	y = (int)(g->ray.pos.y + g->ray.direction.x * g->rndr.move_speed);
	if (g->ray.map[(int)g->ray.pos.y][x] == '0')
		g->ray.pos.x -= g->ray.direction.y * g->rndr.move_speed;
	if (g->ray.map[y][(int)g->ray.pos.x] == '0')
		g->ray.pos.y += g->ray.direction.x * g->rndr.move_speed;
}

void	move(t_game *g, int key)
{
	if (key == 13|| key == 1)
		back_and_forward(g, key);
	else
		left_and_right(g, key);
}

int	key_hook(int key, t_game *g)
{
	// printf("key : %d\n", key);
	g->rndr.move_speed = 0.08;
	if (key == 124)
		turn_angle(g, key);
	if (key == 123)
		turn_angle(g, key);
	if (key == 13 || key == 1)
		move(g, key);
	if (key == 0 || key == 2)
		move(g, key);
	if (key == 53)
		exit_game(g);
	draw(g);
	return (key);
}
