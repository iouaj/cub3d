/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:54:15 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/12 17:58:09 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_wall_height(double distance)
{
	return ((int)(WIN_HEIGHT / distance));
}

void	draw_line(int x, int drawStart, int drawEnd, int color, t_img *img, t_data *d)
{
	int	y;

	y = 0;
	while (y < drawStart)
	{
		pixel_put_img(img, x, y, rgb_to_decimal(d->ceiling));
		y++;
	}
	while (y < drawEnd)
	{
		pixel_put_img(img, x, y, color);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		pixel_put_img(img, x, y, rgb_to_decimal(d->floor));
		y++;
	}
}

void	find_wall(t_ray *ray, char **map, int x, t_img *img, t_data *d)
{
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;

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
	if (ray->hitside == VERTICAL)
	{
		perpWallDist = (ray->mapX - d->pos_x + (1 - ray->stepX) / 2) / ray->rayDirX;
		color = BLUE;
	}
	else
	{
		perpWallDist = (ray->mapY - d->pos_y + (1 - ray->stepY) / 2) / ray->rayDirY;
		color = GREEN;
	}

	lineHeight = get_wall_height(perpWallDist);
	drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;
	draw_line(x, drawStart, drawEnd, color, img, d);
}

void	raycasting(t_data *d, int x, t_img *img)
{
	t_ray	ray;
	ray = create_ray(x, d);
	find_wall(&ray, d->map, x, img, d);
}
