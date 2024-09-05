/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:01:21 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/05 16:20:46 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

int	checkline(char	*line)
{
	size_t	i;

	if (!line)
		return (0);
	i = ft_strlen(line);
	if (i > 0 && line[i - 1] == '\n')
		return (1);
	return (0);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;

	i = 0;
	while (s[i])
		i++;
	dup = malloc(sizeof(char) * i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	*removeline(char *prev, char *line, char *buffer)
{
	size_t	i;
	char	*newprev;

	i = 0;
	free(buffer);
	while (prev[i] && prev[i] == line[i])
		i++;
	newprev = ft_strdup(prev + i);
	if (!newprev)
	{
		free(prev);
		return (NULL);
	}
	free(prev);
	if (newprev[0] == 0)
	{
		free(newprev);
		return (NULL);
	}
	return (newprev);
}

char	*setline(char *line, char *prev, char *buffer)
{
	char	*templine;

	templine = ft_join(prev, buffer);
	if (line)
		free(line);
	if (!templine)
		return (NULL);
	return (templine);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*prevread = NULL;
	int			r;

	line = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	r = 1;
	while (!checkline(line) && r != 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
			return (freeall(line, buffer, prevread));
		buffer[r] = 0;
		line = setline(line, prevread, buffer);
		if (!line)
			return (freeall(line, buffer, prevread));
		prevread = ft_strjoin_prev(prevread, buffer);
		if (!prevread)
			return (freeall(line, buffer, prevread));
	}
	prevread = removeline(prevread, line, buffer);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int main(void)
// {
// 	int	fd = open("test", O_RDONLY);
// 	int i = 1;
// 	char	*line;

// 	printf("Buffer Size : %d\n", BUFFER_SIZE);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("Line %i : %s", i, line);
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	close(fd);
// }
