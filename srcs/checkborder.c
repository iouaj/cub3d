/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkborder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:06:23 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/15 15:07:01 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	valid_value(char c)
{
	if (c == WALL)
		return (TRUE);
	if (c == SPACE)
		return (TRUE);
	if (c == 'A')
		return (TRUE);
	return (FALSE);
}

static int	case_valid(int x, int y, char **map)
{
	if (x + 1 >= (int)ft_strlen(map[y]) || valid_value(map[y][x + 1]) == FALSE)
		return (FALSE);
	if (x - 1 < 0 || valid_value(map[y][x - 1]) == FALSE)
		return (FALSE);
	if (y + 1 >= (int)size_tab(map) || x >= (int)ft_strlen(map[y + 1])
		|| valid_value(map[y + 1][x]) == FALSE)
		return (FALSE);
	if (y - 1 < 0 || x >= (int)ft_strlen(map[y - 1])
		|| valid_value(map[y - 1][x]) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	check_border(int x, int y, char **map)
{
	if (x < 0 || y < 0 || y > (int)size_tab(map)
		|| x > (int)ft_strlen(map[y]) || !map[y][x])
		return (FALSE);
	if (map[y][x] == SPACE || map[y][x] == 'N' || map[y][x] == 'W'
		|| map[y][x] == 'S' || map[y][x] == 'E')
	{
		if (case_valid(x, y, map) == FALSE)
			return (FALSE);
		else
		{
			map[y][x] = 'A';
			return (check_border(x - 1, y, map) + check_border(x + 1, y, map)
				+ check_border(x, y - 1, map) + check_border(x, y + 1, map));
		}
	}
	return (TRUE);
}
