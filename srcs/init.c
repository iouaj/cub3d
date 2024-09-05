/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:21:59 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/05 18:28:48 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_search_keyword_line(char **descriptor, char *keyword)
{
	size_t	i;
	char	*line;

	i = 0;
	while (descriptor && descriptor[i])
	{
		line = ft_strtrim(descriptor[i], " \n\t\v\r\f");
		if (!line)
			return (NULL);
		if (!ft_strncmp(line, keyword, ft_strlen(keyword)))
			return (line);
		free(line);
		i++;
	}
	return (NULL);
}

char	*get_path(char *line, char *keyword)
{
	char	*temp;

	temp = ft_substr(line, ft_strlen(keyword), ft_strlen(line) - ft_strlen(keyword));
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

t_texture	set_texture(char **descriptor, char *keyword)
{
	char	*line;
	t_texture	t;

	t.id = keyword;
	t.path = NULL;
	line = ft_search_keyword_line(descriptor, keyword);
	if (!line)
		return (t);
	t.path = get_path(line, keyword);
	return (t);
}

t_rgb	get_rgb(char *line, char *keyword)
{
	t_rgb	rgb;
	char	**splitter;
	char	*temp;

	rgb.r = -1;
	rgb.g = -1;
	rgb.b = -1;
	temp = ft_substr(line, ft_strlen(keyword), ft_strlen(line) - ft_strlen(keyword));
	free(line);
	line = temp;
	splitter = ft_split(line, ',');
	free(line);
	if (!splitter || size_tab(splitter) != 3)
		return (rgb);
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

void	print_color(t_color c)
{
	printf("ID : %s\n", c.id);
	printf("RGB : %d,%d,%d\n", c.rgb.r, c.rgb.g, c.rgb.b);
}

void	print_texture(t_texture t)
{
	printf("ID : %s\n", t.id);
	printf("Path : %s\n", t.path);
}

t_data	*init_data(char **descriptor)
{
	t_data	*d;

	d = malloc(sizeof(t_data));
	if (!d)
		return (NULL);

	d->textures[NO] = set_texture(descriptor, "NO");
	d->textures[SO] = set_texture(descriptor, "SO");
	d->textures[WE] = set_texture(descriptor, "WE");
	d->textures[EA] = set_texture(descriptor, "EA");
	d->ceiling = set_color(descriptor, "C");
	d->floor = set_color(descriptor, "F");

	print_color(d->ceiling);
	print_color(d->floor);
	return (d);
}
