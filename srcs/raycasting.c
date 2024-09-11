/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:54:15 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/11 14:06:11 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//x variable if vertical wall
//y variable if horizontal wall
double	get_distance(int map, double pos, double step, double rayDir)
{
	return ((map - pos + (1 - step) / 2) / rayDir);
}

int	get_wall_height(double distance)
{
	return (WIN_HEIGHT / distance);
}

void	find_wall(t_ray *ray, char **map)
{
	// printf("DeltaDistX %f\n", ray->deltaDistX);
	// printf("DeltaDistY %f\n", ray->deltaDistY);

	// printf("sideDistX %f\n", sideDistX);
	// printf("sideDistY %f\n", sideDistY);
	while (map[ray->mapY][ray->mapX] != WALL)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->mapX += ray->stepX;
			ray->sideDistX += ray->deltaDistX;
			ray->hitside = VERTICAL;
		}
		else
		{
			ray->mapY += ray->stepY;
			ray->sideDistY += ray->deltaDistY;
			ray->hitside = HORIZONTAL;
		}
	}
	// printf("Il y a un mur en (%d, %d)\n", ray->mapX, ray->mapY);
	(void) ray->hitside;
	return ;

}

void	check_horizontal(t_data *d, int angle)
{
	t_ray	ray;
	// printf("angle %d\n", angle);
	ray = create_ray(angle, d);
	find_wall(&ray, d->map);
	// printf("--------------------------\n");
}
