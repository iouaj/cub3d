/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:54:57 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/17 17:58:14 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_texture	get_texture(t_data *d, t_ray *ray)
{
	if (ray->hitside == HORIZONTAL)
	{
		if (ray->step_y == -1)
			return (d->textures[NO]);
		else
			return (d->textures[SO]);
	}
	else
	{
		if (ray->step_x == -1)
			return (d->textures[WE]);
		else
			return (d->textures[EA]);
	}
}

static void	set_coor_texture(t_ray *ray, t_texture *t, t_data *d)
{
	double	wall;

	if (ray->hitside == VERTICAL)
		wall = d->pos_y + ray->per_wall_dist * ray->raydir_y;
	else
		wall = d->pos_x + ray->per_wall_dist * ray->raydir_x;
	wall -= floor(wall);
	t->text_x = (int)(wall * (double)t->width);
	if (ray->hitside == VERTICAL && ray->raydir_x > 0)
		t->text_x = t->width - t->text_x - 1;
	if (ray->hitside == HORIZONTAL && ray->raydir_y < 0)
		t->text_x = t->width - t->text_x - 1;
}

static void	draw_texture(t_data *d, t_ray *ray, int x, t_img *img)
{
	t_texture	text;
	double		step;
	double		text_pos;
	int			y;
	int			color;

	text = get_texture(d, ray);
	set_coor_texture(ray, &text, d);
	step = 1.0 * text.height / ray->line_height;
	text_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		text.text_y = (int)text_pos & (text.height - 1);
		text_pos += step;
		if (text.id == NO || text.id == SO)
			color = (*(int *)(text.addr + (4 * text.width * text.text_y)
						+ 4 * text.text_x));
		else
			color = (*(int *)(text.addr + (4 * text.width * text.text_y)
						+ 4 * (text.width - text.text_x - 1)));
		pixel_put_img(img, x, y, color);
		y++;
	}
}

void	draw_line(int x, t_img *img, t_data *d, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		pixel_put_img(img, x, y, rgb_to_decimal(d->ceiling));
		y++;
	}
	draw_texture(d, ray, x, img);
	y = ray->draw_end;
	while (y < WIN_HEIGHT)
	{
		pixel_put_img(img, x, y, rgb_to_decimal(d->floor));
		y++;
	}
}
