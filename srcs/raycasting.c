/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:54:15 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/11 17:35:35 by iouajjou         ###   ########.fr       */
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
	return ((int)(WIN_HEIGHT / distance));
}

void	draw_line(int x, int drawStart, int drawEnd, int color, t_img *img)
{
	int	y;

	y = drawStart;
	while (y < drawEnd)
	{
		pixel_put_img(img, x, y, color);
		y++;
	}
}

void	find_wall(t_ray *ray, char **map, int x, t_img *img)
{
	double	perpWallDist;
	int		lineHeight;
	int drawStart;
	int drawEnd;
	int	color;

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
	// printf("SideDist : %f - Delta Dist : %f = %f\n", ray->sideDistX, ray->deltaDistX, ray->sideDistX - ray->deltaDistX);
	// printf("SideDist : %f - Delta Dist : %f = %f\n", ray->sideDistY, ray->deltaDistY, ray->sideDistY - ray->deltaDistY);

	if (ray->hitside == VERTICAL)
	{
		perpWallDist = ray->sideDistX - ray->deltaDistX;
		color = BLUE;
	}
	else
	{
		perpWallDist = ray->sideDistY - ray->deltaDistY;
		color = GREEN;
	}
	lineHeight = get_wall_height(perpWallDist);
	// printf("lineHeight : %d\n", lineHeight);
	drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
	if(drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;
	draw_line(x, drawStart, drawEnd, color, img);
}

void	raycasting(t_data *d, int angle, int x, t_img *img)
{
	t_ray	ray;
	// printf("angle %d\n", angle);
	ray = create_ray(angle, x, d);
	find_wall(&ray, d->map, x, img);
	// printf("--------------------------\n");
}
