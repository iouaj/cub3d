/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:39:12 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/06 15:01:25 by iouajjou         ###   ########.fr       */
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
	return (1);
}

int	render(t_data *d)
{
	static int	i = 0;

	if (i == 0)
	{
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->textures[NO].img, 0, 0);
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
