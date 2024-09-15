/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:42:27 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/15 17:33:29 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_position_free(t_data *d, double x, double y)
{
	if (y >= 0 && y < size_tab(d->map) && x >= 0
		&& x < ft_strlen(d->map[(int)y]))
	{
		if (d->map[(int)y][(int)x] != '1')
			return (TRUE);
	}
	return (FALSE);
}

void	front_move(t_data *d)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = d->pos_x + d->dir_x * MOVE_SPEED;
	new_pos_y = d->pos_y + d->dir_y * MOVE_SPEED;
	if (is_position_free(d, new_pos_x, d->pos_y) == TRUE)
		d->pos_x = new_pos_x;
	if (is_position_free(d, d->pos_x, new_pos_y) == TRUE)
		d->pos_y = new_pos_y;
	d->action++;
}

void	back_move(t_data *d)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = d->pos_x - d->dir_x * MOVE_SPEED;
	new_pos_y = d->pos_y - d->dir_y * MOVE_SPEED;
	if (is_position_free(d, new_pos_x, d->pos_y) == TRUE)
		d->pos_x = new_pos_x;
	if (is_position_free(d, d->pos_x, new_pos_y) == TRUE)
		d->pos_y = new_pos_y;
	d->action++;
}

void	left_move(t_data *d)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = d->pos_x + d->dir_y * MOVE_SPEED;
	new_pos_y = d->pos_y + -d->dir_x * MOVE_SPEED;
	if (is_position_free(d, new_pos_x, d->pos_y) == TRUE)
		d->pos_x = new_pos_x;
	if (is_position_free(d, d->pos_x, new_pos_y) == TRUE)
		d->pos_y = new_pos_y;
	d->action++;
}

void	right_move(t_data *d)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = d->pos_x + -d->dir_y * MOVE_SPEED;
	new_pos_y = d->pos_y + d->dir_x * MOVE_SPEED;
	if (is_position_free(d, new_pos_x, d->pos_y) == TRUE)
		d->pos_x = new_pos_x;
	if (is_position_free(d, d->pos_x, new_pos_y) == TRUE)
		d->pos_y = new_pos_y;
	d->action++;
}
