/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:21:51 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/18 13:06:02 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_right(t_data *d)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = d->dir_x;
	d->dir_x = d->dir_x * cos(ROT_SPEED) - d->dir_y * sin(ROT_SPEED);
	d->dir_y = old_dir_x * sin(ROT_SPEED) + d->dir_y * cos(ROT_SPEED);
	old_plane_x = d->plane_x;
	d->plane_x = d->plane_x * cos(ROT_SPEED) - d->plane_y * sin(ROT_SPEED);
	d->plane_y = old_plane_x * sin(ROT_SPEED) + d->plane_y * cos(ROT_SPEED);
}

void	rotate_left(t_data *d)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = d->dir_x;
	d->dir_x = d->dir_x * cos(-ROT_SPEED) - d->dir_y * sin(-ROT_SPEED);
	d->dir_y = old_dir_x * sin(-ROT_SPEED) + d->dir_y * cos(-ROT_SPEED);
	old_plane_x = d->plane_x;
	d->plane_x = d->plane_x * cos(-ROT_SPEED) - d->plane_y * sin(-ROT_SPEED);
	d->plane_y = old_plane_x * sin(-ROT_SPEED) + d->plane_y * cos(-ROT_SPEED);
}

double	get_margin(double dir)
{
	if (dir > 0)
		return (0.25);
	if (dir == 0)
		return (0);
	return (-0.25);
}
