/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:17:33 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/19 14:59:57 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_rgb	get_rgb(char *line, char *key)
{
	t_rgb	rgb;
	char	**splitter;
	char	*temp;

	rgb.r = -1;
	rgb.g = -1;
	rgb.b = -1;
	temp = ft_substr(line, ft_strlen(key), ft_strlen(line) - ft_strlen(key));
	free(line);
	line = temp;
	splitter = ft_split(line, ',');
	free(line);
	if (!splitter || size_tab(splitter) != 3)
	{
		free_tab(splitter);
		return (rgb);
	}
	rgb.r = ft_atoi(splitter[0]);
	rgb.g = ft_atoi(splitter[1]);
	rgb.b = ft_atoi(splitter[2]);
	free_tab(splitter);
	return (rgb);
}

t_color	set_color(char	**descriptor, char *keyword)
{
	char	*line;
	t_color	c;

	c.id = keyword;
	c.rgb.r = -1;
	c.rgb.g = -1;
	c.rgb.b = -1;
	line = ft_search_keyword_line(descriptor, keyword);
	if (!line)
		return (c);
	c.rgb = get_rgb(line, keyword);
	return (c);
}

void	get_colors(t_data *d)
{
	d->ceiling = set_color(d->descriptor, "C");
	d->floor = set_color(d->descriptor, "F");
}

int	check_color(t_color c, t_data *d)
{
	int	trig;

	trig = TRUE;
	if (c.rgb.r < 0 || c.rgb.r > 255)
		trig = FALSE;
	else if (c.rgb.g < 0 || c.rgb.g > 255)
		trig = FALSE;
	else if (c.rgb.b < 0 || c.rgb.b > 255)
		trig = FALSE;
	if (trig == FALSE)
	{
		ft_putstr_fd("Invalid color\n", 2);
		d->map = NULL;
		free_data(d);
		return (trig);
	}
	return (trig);
}
