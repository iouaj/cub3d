/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:11:31 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/11 17:15:33 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	get_direction_x(t_data *d, int x)
{
	double	rayDirecX;
	double	cameraX;

	cameraX = 2 * x / (double)WIN_WIDTH - 1;
	rayDirecX = d->dirX + d->planeX * cameraX;
	return (rayDirecX);
}

static double	get_direction_y(t_data *d, int x)
{
	double	rayDirectY;
	double	cameraX;

	cameraX = 2 * x / (double)WIN_WIDTH - 1;
	rayDirectY = d->dirY + d->planeY * cameraX;
	return (rayDirectY);
}

static int	get_step(double rayDir)
{
	if (rayDir < 0)
		return (-1);
	return (1);
}

static double	get_sideDist(double pos, int map, double deltaDist, int step)
{
	double	sideDist;

	if (step == 1)
		sideDist = (map + 1.0 - pos) * deltaDist;
	else
		sideDist = (pos - map) * deltaDist;
	return (sideDist);
}

t_ray	create_ray(int angle, int x, t_data *d)
{
	t_ray	ray;

	ray.angle = angle;
	ray.rayDirX = get_direction_x(d, x);
	ray.rayDirY = get_direction_y(d, x);
	ray.deltaDistX = sqrt(1 + pow(ray.rayDirY / ray.rayDirX, 2));
	ray.deltaDistY = sqrt(1 + pow(ray.rayDirX / ray.rayDirY, 2));
	ray.mapX = (int)d->pos_x;
	ray.mapY = (int)d->pos_y;
	ray.stepX = get_step(ray.rayDirX);
	ray.stepY = get_step(ray.rayDirY);
	ray.sideDistX = get_sideDist(d->pos_x, ray.mapX, ray.deltaDistX, ray.stepX);
	ray.sideDistY = get_sideDist(d->pos_x, ray.mapY, ray.deltaDistY, ray.stepY);
	ray.hitside = -1;
	return (ray);
}
