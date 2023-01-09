/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@42kocaeli.com.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:07:43 by merkol            #+#    #+#             */
/*   Updated: 2023/01/09 16:07:43 by merkol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	if (dir == 0)
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
	if (key == 13 || key == 1)
		back_and_forward(g, key);
	else
		left_and_right(g, key);
}

int	key_hook(int key, t_game *g)
{
	g->rndr.move_speed = 0.40;
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
	return (key);
}
