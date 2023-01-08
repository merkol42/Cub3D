#include "../../include/cub3d.h"

// void	print_ray(t_ray *ray)
// {
// 	int i = -1;
// 	printf("\nmap: \n\n");
// 	while (ray->map[++i] != 0)
// 		printf("map[i]: |%s|\n", ray->map[i]);
// 	printf("map_width: [%d]\n", ray->map_width);
// 	printf("map_height: [%d]\n", ray->map_height);
// 	printf("hit: [%d]\n", ray->hit);
// 	printf("side: [%d]\n", ray->side);
// 	printf("fov: [%f]\n", ray->fov);
// 	printf("camerstart_x: [%f]\n", ray->camerstart_x);
// 	printf("perp_wall_dist: [%f]\n", ray->perp_wall_dist);
// 	printf("pos: x:[%f] y: [%f]\n", ray->pos.x, ray->pos.y);
// 	printf("in_map: x:[%f] y: [%f]\n", ray->in_map.x, ray->in_map.y);
// 	printf("res: x:[%f] y: [%f]\n", ray->res.x, ray->res.y);
// 	printf("plane: x:[%f] y: [%f]\n", ray->plane.x, ray->plane.y);
// 	printf("direction: x:[%f] y: [%f]\n",
// 			ray->direction.x, ray->direction.y);
// 	printf("ray_dir: x:[%f] y: [%f]\n", ray->ray_dir.x, ray->ray_dir.y);
// 	printf("delta_dist: x:[%f] y: [%f]\n",
// 						ray->delta_dist.x, ray->delta_dist.y);
// 	printf("side_dist: x:[%f] y: [%f]\n",
// 					ray->side_dist.x, ray->side_dist.y);
// 	printf("step: x:[%f] y: [%f]\n", ray->step.x, ray->step.y);
// }

void	setup_ray(t_ray *r, int i)
{
	r->camera_x = 2 * i / r->res.x - 1;
	r->ray_dir.x = r->direction.x - r->plane.x * r->camera_x;
	r->ray_dir.y = r->direction.y - r->plane.y * r->camera_x;
	r->in_map.x = (int)(r->pos.x);
	r->in_map.y = (int)(r->pos.y);
	r->delta_dist.x = fabs(1 / r->ray_dir.x);
	r->delta_dist.y = fabs(1 / r->ray_dir.y);
	r->hit = 0;
}

void	ray_step_and_dist(t_ray *r)
{
	if (r->ray_dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (r->pos.x - r->in_map.x) * r->delta_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (r->in_map.x + 1 - r->pos.x) * r->delta_dist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = (r->pos.y - r->in_map.y) * r->delta_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->in_map.y + 1 - r->pos.y) * r->delta_dist.y;
	}
}

void	dda(t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->in_map.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->in_map.y += r->step.y;
			r->side = 1;
		}
		if (r->map[(int)r->in_map.y][(int)r->in_map.x] == '1')
			r->hit = 1;
	}
	
}

void	check_limit(t_ray *r)
{
	if (r->line.start_x < 0)
	{
		r->line.start_x = 0;
		r->line.end_x = 0;
	}
	if (r->line.start_x > r->render.res_width)
	{
		r->line.start_x  = r->render.res_width;
		r->line.end_x = r->render.res_width;
	}
	if (r->line.start_y < 0)
		r->line.start_y = 0;
	if (r->line.end_y < 0)
		r->line.end_y = 0;
	if (r->line.end_y > r->render.res_height)
		r->line.end_y = r->render.res_height;
	if (r->line.start_y > r->render.res_height)
		r->line.start_y = r->render.res_height;
}

int	sign(float x)
{
	if (x > 0)
		return (1);
	else if (x < 0)
		return (-1);
	return (0);
}

void	line_draw(t_ray *r)
{
	while (r->line.start_x != r->line.end_x || r->line.start_y != r->line.end_y)
	{
		img_pix_put(&r->render.img, r->line.start_x, r->line.start_y, 0x0000ff);
		r->line.start_x += r->line.delta.x;
		r->line.start_y += r->line.delta.y;
	}
}

void	distance_and_line(t_ray *r, int x)
{
	int		h;
	double	line_height;

	h = r->render.res_height;
	if (r->side == 0)
	{
		// (r->in_map.x - r->pos.x + (1 - r->step.x) / 2) / r->ray_dir.x;
		r->perp_wall_dist = r->side_dist.x - r->delta_dist.x;
	}
	else
	{
		// (r->in_map.y - r->pos.y + (1 - r->step.y) / 2) / r->ray_dir.y;
		r->perp_wall_dist = r->side_dist.y - r->delta_dist.y;
	}
	line_height = (int)(h / r->perp_wall_dist);
	r->line.len = line_height;
	r->line.start_x = x;
	r->line.start_y = -line_height / 2 + h / 2;
	r->line.end_x = x;
	r->line.end_y = line_height / 2 + h / 2;
	r->line.delta.x = sign(r->line.end_x - r->line.start_x); // 0
	r->line.delta.y = sign(r->line.end_y - r->line.start_y); // 1 always
	check_limit(r);
}

void	raycaster(t_ray *r)
{
	int	i;

	i = -1;
	while (++i < WIN_WIDTH)
	{
		setup_ray(r, i);
		ray_step_and_dist(r);
		dda(r);
		distance_and_line(r, i);
		line_draw(r);
		// texture(r, i);
	}
}