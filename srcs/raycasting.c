/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:54:15 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/17 17:57:48 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_draw_range(t_ray *ray, t_data *d)
{
	if (ray->hitside == VERTICAL)
	{
		ray->per_wall_dist = (ray->map_x - d->pos_x + (1 - ray->step_x) / 2)
			/ ray->raydir_x;
	}
	else
	{
		ray->per_wall_dist = (ray->map_y - d->pos_y + (1 - ray->step_y) / 2)
			/ ray->raydir_y;
	}
	ray->line_height = (int)(WIN_HEIGHT / ray->per_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0 || ray->draw_start >= WIN_HEIGHT)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT || ray->draw_end < 0)
		ray->draw_end = WIN_HEIGHT - 1;
}

static void	find_wall(t_ray *ray, int x, t_img *img, t_data *d)
{
	while (d->map[ray->map_y][ray->map_x] != WALL)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->map_x += ray->step_x;
			ray->side_dist_x += ray->delta_dist_x;
			ray->hitside = VERTICAL;
		}
		else
		{
			ray->map_y += ray->step_y;
			ray->side_dist_y += ray->delta_dist_y;
			ray->hitside = HORIZONTAL;
		}
	}
	get_draw_range(ray, d);
	draw_line(x, img, d, ray);
}

void	raycasting(t_data *d, int x, t_img *img)
{
	t_ray	ray;

	ray = create_ray(x, d);
	find_wall(&ray, x, img, d);
}
