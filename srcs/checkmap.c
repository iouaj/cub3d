/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:51:26 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/06 18:28:17 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	follow_wall(int x, int y, char **map)
{
	if ()
}


int	next_to_wall(int x, int y, char **map)
{
	if (map[y][x + 1] == WALL)
		return (TRUE);
	if (map[y + 1][x] == WALL)
		return (TRUE);
	if (map[y][x - 1] == WALL)
		return (TRUE);
	if (map[y - 1][x] == WALL)
		return (TRUE)
	return (FALSE);
}

int	check_border(int x, int y, char **map)
{
	while (map[y][x] && next_to_wall(x, y, char **map) == FALSE)
		x++;
	if (map[y][x] == 0)
		return (FALSE);
	map[y][x] = 'A';
	return (FALSE);
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
	if (check_carac(map, "10NSEW \t\v\n\r\f") == FALSE)
		return (FALSE);
	if (check_start_position(map, d) == FALSE)
		return (FALSE);
	copy = ft_deep_copy_tab(map);
	if (!copy)
		return (FALSE);
	if (check_border(d->pos_x, d->pos_y, copy) == FALSE)
	{
		free(copy);
		return (FALSE);
	}
	free(copy);
	return (TRUE);
}
