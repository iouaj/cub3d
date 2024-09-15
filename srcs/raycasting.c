/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:54:15 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/15 13:24:29 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_wall_height(double distance)
{
	return ((int)(WIN_HEIGHT / distance));
}

t_texture	get_texture(t_data *d, t_ray *ray)
{
	if (ray->hitside == HORIZONTAL)
	{
		if (ray->stepY == -1)
			return (d->textures[NO]);
		else
			return (d->textures[SO]);
	}
	else
	{
		if (ray->stepX == -1)
			return (d->textures[WE]);
		else
			return (d->textures[EA]);
	}
}

void	set_coor_texture(t_ray *ray, t_texture *t, double perpWallDist, t_data *d)
{
	double	wall;

	if (ray->hitside == VERTICAL)
		wall = d->pos_y + perpWallDist * ray->rayDirY;
	else
		wall = d->pos_x + perpWallDist * ray->rayDirX;
	printf("wall after floor %f\n", wall);
	// if (wall - floor(wall) != 0)
	wall -= floor(wall);
	t->textX = (int)(wall * (double)t->width);
	// printf("textX in coor %d\n", t->textX);
	if (ray->hitside == VERTICAL && ray->rayDirX > 0)
		t->textX = t->width - t->textX - 1;
	if (ray->hitside == HORIZONTAL && ray->rayDirY < 0)
		t->textX =  t->width - t->textX - 1;
}

void	draw_texture(t_data *d, t_ray *ray, int x, int drawStart, int drawEnd, t_img *img)
{
	t_texture	text;
	double	step;
	double	textPos;
	int		y;
	int		textY;
	int		color;

	text = get_texture(d, ray);
	set_coor_texture(ray, &text, ray->perpWallDist, d);
	step = 1.0 * text.height / ray->lineHeight;
	// printf("step : %f\n", step);
	textPos = (drawStart - WIN_HEIGHT / 2 + ray->lineHeight / 2) * step;
	y = drawStart;
	// printf("textX %d\n", text.textX);
	while (y < drawEnd)
	{
		textY = (int)textPos & (text.height - 1);
		textPos += step;
		color = (*(int *)(text.addr + (4 * text.width * textY) + 4 * text.textX));
		pixel_put_img(img, x, y, color);
		y++;
	}
}

void	draw_line(int x, int drawStart, int drawEnd, int color, t_img *img, t_data *d, t_ray *ray)
{
	int	y;

	y = 0;
	(void) color;
	while (y < drawStart)
	{
		pixel_put_img(img, x, y, rgb_to_decimal(d->ceiling));
		y++;
	}
	draw_texture(d, ray, x, drawStart, drawEnd, img);
	y = drawEnd;
	while (y < WIN_HEIGHT)
	{
		pixel_put_img(img, x, y, rgb_to_decimal(d->floor));
		y++;
	}
}

void	find_wall(t_ray *ray, char **map, int x, t_img *img, t_data *d)
{
	// double	perpWallDist;
	// int		lineHeight;
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
	// printf("wall in (%d, %d)\n", ray->mapX, ray->mapY);
	if (ray->hitside == VERTICAL)
	{
		ray->perpWallDist = (ray->mapX - d->pos_x + (1 - ray->stepX) / 2) / ray->rayDirX;
		// perpWallDist = ray->sideDistX - ray->deltaDistX;
		color = BLUE;
	}
	else
	{
		ray->perpWallDist = (ray->mapY - d->pos_y + (1 - ray->stepY) / 2) / ray->rayDirY;
		// perpWallDist = ray->sideDistY - ray->deltaDistY;
		color = GREEN;
	}

	ray->lineHeight = get_wall_height(ray->perpWallDist);
	drawStart = -ray->lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = ray->lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;
	draw_line(x, drawStart, drawEnd, color, img, d, ray);
}

void	raycasting(t_data *d, int x, t_img *img)
{
	t_ray	ray;
	ray = create_ray(x, d);
	find_wall(&ray, d->map, x, img, d);
}
