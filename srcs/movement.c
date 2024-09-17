/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:42:27 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/17 18:07:05 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_position_free(t_data *d, double x, double y)
{
	if (y > 0 && y < (double)(size_tab(d->map)) && x > 0
		&& x < (double)(ft_strlen(d->map[(int)y])))
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
	double	margin_x;
	double	margin_y;

	margin_x = get_margin(d->dir_x);
	margin_y = get_margin(d->dir_y);
	if (is_position_free(d, d->pos_x + margin_x, d->pos_y + margin_y) == FALSE)
		return ;
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
	double	margin_x;
	double	margin_y;

	margin_x = get_margin(d->dir_x);
	margin_y = get_margin(d->dir_y);
	if (is_position_free(d, d->pos_x - margin_x, d->pos_y - margin_y) == FALSE)
		return ;
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
	double	margin_x;
	double	margin_y;

	margin_x = get_margin(d->dir_x);
	margin_y = get_margin(d->dir_y);
	if (is_position_free(d, d->pos_x + margin_y, d->pos_y + -margin_x) == FALSE)
		return ;
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
	double	margin_x;
	double	margin_y;

	margin_x = get_margin(d->dir_x);
	margin_y = get_margin(d->dir_y);
	if (is_position_free(d, d->pos_x + -margin_y, d->pos_y + margin_x) == FALSE)
		return ;
	new_pos_x = d->pos_x + -d->dir_y * MOVE_SPEED;
	new_pos_y = d->pos_y + d->dir_x * MOVE_SPEED;
	if (is_position_free(d, new_pos_x, d->pos_y) == TRUE)
		d->pos_x = new_pos_x;
	if (is_position_free(d, d->pos_x, new_pos_y) == TRUE)
		d->pos_y = new_pos_y;
	d->action++;
}
