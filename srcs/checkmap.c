/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:51:26 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/15 21:23:40 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_dir(t_data *d, char c)
{
	if (c == 'N')
	{
		d->dir_x = 0;
		d->dir_y = -1;
	}
	else if (c == 'S')
	{
		d->dir_x = 0;
		d->dir_y = 1;
	}
	else if (c == 'W')
	{
		d->dir_x = -1;
		d->dir_y = 0;
	}
	else if (c == 'E')
	{
		d->dir_x = 1;
		d->dir_y = 0;
	}
	d->plane_x = -d->dir_y * 0.66;
	d->plane_y = d->dir_x * 0.66;
}

int	check_start_position(char **map, t_data *d)
{
	size_t	i;
	size_t	j;
	int		trigger;

	i = 0;
	trigger = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_in_set("NSEW", map[i][j]) == TRUE)
			{
				trigger++;
				d->pos_x = j;
				d->pos_y = i;
				set_dir(d, map[i][j]);
			}
			j++;
		}
		i++;
	}
	if (trigger == 1)
		return (TRUE);
	return (FALSE);
}

static int	check_carac(char **map, char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_in_set(set, map[i][j]) == FALSE)
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	is_map_valid(char **map, t_data *d)
{
	char	**copy;

	if (size_tab(map) < 3)
		return (FALSE);
	if (check_carac(map, "10NSEW ") == FALSE)
		return (FALSE);
	if (check_start_position(map, d) == FALSE)
		return (FALSE);
	copy = ft_deep_copy_tab(map);
	if (!copy)
		return (FALSE);
	if (check_border(d->pos_x, d->pos_y, copy) == FALSE)
	{
		free_tab(copy);
		return (FALSE);
	}
	free_tab(copy);
	return (TRUE);
}
