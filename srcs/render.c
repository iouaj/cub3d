/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:39:12 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/12 15:31:43 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	leave(t_data *d)
{
	free_data(d);
	exit(EXIT_SUCCESS);
}

void	rotate_left(t_data *d)
{
	double oldDirX = d->dirX;
	d->dirX = d->dirX * cos(ROT_SPEED) - d->dirY * sin(ROT_SPEED);
	d->dirY = oldDirX * sin(ROT_SPEED) + d->dirY * cos(ROT_SPEED);
	double oldPlaneX = d->planeX;
	d->planeX = d->planeX * cos(ROT_SPEED) - d->planeY * sin(ROT_SPEED);
	d->planeY = oldPlaneX * sin(ROT_SPEED) + d->planeY * cos(ROT_SPEED);
	d->action++;
}

void	rotate_right(t_data *d)
{
	double oldDirX = d->dirX;
	d->dirX = d->dirX * cos(-ROT_SPEED) - d->dirY * sin(-ROT_SPEED);
	d->dirY = oldDirX * sin(-ROT_SPEED) + d->dirY * cos(-ROT_SPEED);
	double oldPlaneX = d->planeX;
	d->planeX = d->planeX * cos(-ROT_SPEED) - d->planeY * sin(-ROT_SPEED);
	d->planeY = oldPlaneX * sin(-ROT_SPEED) + d->planeY * cos(-ROT_SPEED);
	d->action++;
}

int	handle_keypress(int key, t_data *d)
{
	if (key == ESC)
		leave(d);
	else if (key == LEFT_CAM)
		rotate_left(d);
	else if (key == RIGHT_CAM)
		rotate_right(d);
	else if (key == FRONT)
		front_move(d);
	else if (key == BACK)
		back_move(d);
	else if (key == RIGHT)
		right_move(d);
	else if (key == LEFT)
		left_move(d);
	else
		printf("Key : %d\n", key);
	return (1);
}

int	render(t_data *d)
{
	static size_t	i = 0;
	t_img	*img;


	if (i <= d->action)
	{
		img = create_img(d);
		if (!img)
		{
			ft_putstr_fd("Fail to create img.\n", 2);
			free_data(d);
			exit(EXIT_FAILURE);
		}
		// printf("(%f,%f)\n", d->pos_x, d->pos_y);
		int	x = 0;
		while (x < WIN_WIDTH)
		{
			raycasting(d, x, img);
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
