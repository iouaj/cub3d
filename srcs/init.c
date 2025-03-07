/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:21:59 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/25 14:10:24 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// char	*ft_search_keyword_line(char **descriptor, char *keyword)
// {
// 	size_t	i;
// 	char	*line;
// 	char	*target;
// 	int		trigger;

// 	i = 0;
// 	target = NULL;
// 	trigger = 0;
// 	while (descriptor && descriptor[i])
// 	{
// 		line = ft_strtrim(descriptor[i], " \n\t\v\r\f");
// 		if (!line)
// 			return (NULL);
// 		if (!ft_strncmp(line, keyword, ft_strlen(keyword)))
// 		{
// 			target = line;
// 			trigger++;
// 		}
// 		else
// 			free(line);
// 		i++;
// 	}
// 	if (trigger > 1)
// 		return (NULL);
// 	return (target);
// }

int	check(t_data *d)
{
	if (check_textures(d->textures, d) == FALSE)
		return (FALSE);
	if (check_color(d->ceiling, d) == FALSE
		|| check_color(d->floor, d) == FALSE)
		return (FALSE);
	return (TRUE);
}

char	*get_path(char *line, char *key)
{
	char	*temp;

	temp = ft_substr(line, ft_strlen(key), ft_strlen(line) - ft_strlen(key));
	free(line);
	if (!temp)
		return (NULL);
	line = temp;
	temp = ft_strtrim(line, " \n\t\v\r\f");
	free(line);
	if (!temp)
		return (NULL);
	return (temp);
}

void	set_values(t_data *d, char **descriptor)
{
	d->win_ptr = NULL;
	d->img = NULL;
	d->map = NULL;
	d->textures[NO].img = NULL;
	d->textures[NO].path = NULL;
	d->textures[NO].addr = NULL;
	d->textures[SO].img = NULL;
	d->textures[SO].path = NULL;
	d->textures[SO].addr = NULL;
	d->textures[EA].img = NULL;
	d->textures[EA].path = NULL;
	d->textures[EA].addr = NULL;
	d->textures[WE].img = NULL;
	d->textures[WE].path = NULL;
	d->textures[WE].addr = NULL;
	d->ceiling.id = NULL;
	d->ceiling.rgb.r = -1;
	d->ceiling.rgb.g = -1;
	d->ceiling.rgb.b = -1;
	d->floor.id = NULL;
	d->floor.rgb.r = -1;
	d->floor.rgb.g = -1;
	d->floor.rgb.b = -1;
	d->descriptor = descriptor;
}

void	get_mlx(t_data *d)
{
	d->mlx_ptr = mlx_init();
	if (!d->mlx_ptr)
		return ;
	d->win_ptr = mlx_new_window(d->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
}

t_data	*init_data(char **descriptor)
{
	t_data	*d;
	int		index;

	d = malloc(sizeof(t_data));
	if (!d)
	{
		free_tab(descriptor);
		return (NULL);
	}
	set_values(d, descriptor);
	get_mlx(d);
	if (!d->mlx_ptr || !d->win_ptr)
		return (error_init("Error : can't get mlx\n", d));
	index = parse_descriptor(d);
	if (index == -1)
		return (NULL);
	if (check(d) == FALSE)
		return (NULL);
	d->map = get_map(descriptor, index);
	if (!d->map)
		return (error_init("Error : Invalid Map\n", d));
	free_tab(d->descriptor);
	d->descriptor = NULL;
	return (d);
}
