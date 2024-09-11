/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:39:12 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/11 23:52:06 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	leave(t_data *d)
{
	free_data(d);
	exit(EXIT_SUCCESS);
}

int	handle_keypress(int key, t_data *d)
{
	printf("Key : %d\n", key);
	if (key == ESC)
		leave(d);
	if (key == LEFT)
	{
		printf("LEFT\n");
		double oldDirX = d->dirX;
		d->dirX = d->dirX * cos(ROT_SPEED) - d->dirY * sin(ROT_SPEED);
		d->dirY = oldDirX * sin(ROT_SPEED) + d->dirY * cos(ROT_SPEED);
		double oldPlaneX = d->planeX;
		d->planeX = d->planeX * cos(ROT_SPEED) - d->planeY * sin(ROT_SPEED);
		d->planeY = oldPlaneX * sin(ROT_SPEED) + d->planeY * cos(ROT_SPEED);
		d->action++;
		printf("dirX : %f dirY : %f\n", d->dirX, d->dirY);
	}
	if (key == RIGHT)
	{
		printf("RIGHT");
		double oldDirX = d->dirX;
		d->dirX = d->dirX * cos(-ROT_SPEED) - d->dirY * sin(-ROT_SPEED);
		d->dirY = oldDirX * sin(-ROT_SPEED) + d->dirY * cos(-ROT_SPEED);
		double oldPlaneX = d->planeX;
		d->planeX = d->planeX * cos(-ROT_SPEED) - d->planeY * sin(-ROT_SPEED);
		d->planeY = oldPlaneX * sin(-ROT_SPEED) + d->planeY * cos(-ROT_SPEED);
		d->action++;
		printf("dirX : %f dirY : %f\n", d->dirX, d->dirY);
	}
	if (key == FRONT)
		front_move(d);
	if (key == BACK)
		back_move(d);
	return (1);
}

void	render_ceiling(t_img *img, t_data *d)
{
	int	x;
	int	y;
	int	midline;

	midline = WIN_HEIGHT / 2;
	y = 0;
	while (y < midline)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			pixel_put_img(img, x, y, rgb_to_decimal(d->ceiling));
			x++;
		}
		y++;
	}
}

void	render_floor(t_img *img, t_data *d)
{
	int	x;
	int	y;
	int	midline;

	midline = WIN_HEIGHT / 2;
	y = midline;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			pixel_put_img(img, x, y, rgb_to_decimal(d->floor));
			x++;
		}
		y++;
	}
}

void	render_background(t_img	*img, t_data *d)
{
	render_ceiling(img, d);
	render_floor(img, d);
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, img->img, 0, 0);
}

int	render(t_data *d)
{
	static size_t	i = 0;
	// int	angle;
	t_img	*img;


	if (i == d->action)
	{
		img = create_img(d);
		if (!img)
		{
			ft_putstr_fd("Fail to create img.\n", 2);
			free_data(d);
			exit(EXIT_FAILURE);
		}
		//render_background(img, d);
		printf("(%f,%f)\n", d->pos_x, d->pos_y);
		int	x = 0;
		while (x <= WIN_WIDTH)
		{
			raycasting(d, 60, x, img);
			x++;
		}
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, img->img, 0, 0);
		free_img(d->img, d->mlx_ptr);
		d->img = img;
		i++;
	}
	return (1);
}

void	loop(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, 17, 0, &leave, data);
	mlx_loop(data->mlx_ptr);
}
