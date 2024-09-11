/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:11:31 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/11 12:31:08 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	get_direction_x(t_data *data, double angle)
{
	double	rayDirecX;
	double	dirX;
	double	dirY;
	double	cameraX;
	double	planeX;

	cameraX = 2 * ((data->pos_x + 1) / WIN_HEIGHT) - 1;
	dirX = cos(angle);
	dirY = sin(angle);
	planeX = -dirY * 0.66;
	rayDirecX = dirX + planeX * cameraX;
	return (rayDirecX);
}

static double	get_direction_y(t_data *data, double angle)
{
	double	rayDirectY;
	double	dirX;
	double	dirY;
	double	cameraX;
	double	planeY;

	cameraX = 2 * ((data->pos_x + 1) / WIN_HEIGHT) - 1;
	dirX = cos(angle);
	dirY = sin(angle);
	planeY = dirX * 0.66;
	rayDirectY = dirY + planeY * cameraX;
	return (rayDirectY);
}

static int	get_step(double rayDir)
{
	if (rayDir > 0)
		return (1);
	return (-1);
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

t_ray	create_ray(int angle, t_data *d)
{
	t_ray	ray;

	ray.angle = angle;
	ray.rayDirX = get_direction_x(d, ray.angle);
	ray.rayDirY = get_direction_y(d, ray.angle);
	ray.deltaDistX = sqrt(1 + pow(ray.rayDirY / ray.rayDirX, 2));
	ray.deltaDistY = sqrt(1 + pow(ray.rayDirX / ray.rayDirY, 2));
	ray.posX = d->pos_x;
	ray.posY = d->pos_y;
	ray.mapX = (int)d->pos_x;
	ray.mapY = (int)d->pos_y;
	ray.stepX = get_step(ray.rayDirX);
	ray.stepY = get_step(ray.rayDirY);
	ray.sideDistX = get_sideDist(ray.posX, ray.mapX, ray.deltaDistX, ray.stepX);
	ray.sideDistY = get_sideDist(ray.posY, ray.mapY, ray.deltaDistY, ray.stepY);
	ray.hitside = -1;
	return (ray);
}
