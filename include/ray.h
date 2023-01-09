#ifndef RAY_H
# define RAY_H

#include "cub3d.h"

# define TURN_SPEED 0.20

/////////////////////////////////////
//geometry structs

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_square
{
	double	x;
	double	y;
	double	width;
	double	height;//int dene
}	t_square;

typedef struct s_line
{
	float		start_x;
	float		start_y;
	float		end_x;
	float		end_y;
	float		angle;
	float		len;
	t_point	delta;
}	t_line;

typedef struct s_circle
{
	double	x;
	double	y;
	double	radius;
	double	prox;
	double	trgb;
}	t_circle;

//geometry structs



t_point	assign_point(double x, double y);
t_line	init_line(double a_x, double a_y, double angel, double len);

#endif //RAY_H