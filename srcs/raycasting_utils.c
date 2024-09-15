/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:11:31 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/15 17:27:31 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	get_direction_x(t_data *d, int x)
{
	double	ray_direc_x;
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray_direc_x = d->dir_x + d->plane_x * camera_x;
	return (ray_direc_x);
}

static double	get_direction_y(t_data *d, int x)
{
	double	ray_direc_y;
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray_direc_y = d->dir_y + d->plane_y * camera_x;
	return (ray_direc_y);
}

static int	get_step(double rayDir)
{
	if (rayDir < 0)
		return (-1);
	return (1);
}

static double	get_side_dist(double pos, int map, double deltaDist, int step)
{
	if (step == 1)
		return ((map + 1.0 - pos) * deltaDist);
	else
		return ((pos - map) * deltaDist);
}

t_ray	create_ray(int x, t_data *d)
{
	t_ray	ray;

	ray.raydir_x = get_direction_x(d, x);
	ray.raydir_y = get_direction_y(d, x);
	if (ray.raydir_x == 0)
		ray.delta_dist_x = 1e30;
	else
		ray.delta_dist_x = sqrt(1 + pow(ray.raydir_y / ray.raydir_x, 2));
	if (ray.raydir_y == 0)
		ray.delta_dist_y = 1e30;
	else
		ray.delta_dist_y = sqrt(1 + pow(ray.raydir_x / ray.raydir_y, 2));
	ray.map_x = (int)d->pos_x;
	ray.map_y = (int)d->pos_y;
	ray.step_x = get_step(ray.raydir_x);
	ray.step_y = get_step(ray.raydir_y);
	ray.side_dist_x = get_side_dist(d->pos_x, ray.map_x, ray.delta_dist_x,
			ray.step_x);
	ray.side_dist_y = get_side_dist(d->pos_y, ray.map_y, ray.delta_dist_y,
			ray.step_y);
	ray.hitside = -1;
	return (ray);
}
