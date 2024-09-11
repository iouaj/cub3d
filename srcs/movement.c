/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:42:27 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/12 00:04:15 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_position_free(t_data *d, double x, double y)
{
	if (y >= 0 && y < size_tab(d->map) && x >= 0 && x < ft_strlen(d->map[(int)y]))
	{
		if (d->map[(int)y][(int)x] != '1')
			return (TRUE);
	}
	return (FALSE);
}

void	front_move(t_data *d)
{
	double	new_posX;
	double	new_posY;

	new_posX = d->pos_x + d->dirX * MOVE_SPEED;
	new_posY = d->pos_y + d->dirY * MOVE_SPEED;
	if (is_position_free(d, new_posX, d->pos_y) == TRUE)
		d->pos_x = new_posX;
	if (is_position_free(d, d->pos_x, new_posY) == TRUE)
		d->pos_y = new_posY;
	d->action++;
}

void	back_move(t_data *d)
{
	double	new_posX;
	double	new_posY;

	new_posX = d->pos_x - d->dirX * MOVE_SPEED;
	new_posY = d->pos_y - d->dirY * MOVE_SPEED;
	if (is_position_free(d, new_posX, d->pos_y) == TRUE)
		d->pos_x = new_posX;
	if (is_position_free(d, d->pos_x, new_posY) == TRUE)
		d->pos_y = new_posY;
	d->action++;
}
