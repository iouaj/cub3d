/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:44:07 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/05 16:20:32 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

size_t	ft_strlens(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (s1 == NULL)
		return (ft_strlen(s2));
	if (s2 == NULL)
		return (ft_strlen(s1));
	while (s1 && s1[i])
	{
		if (s1[i] == '\n')
			return (i + 1);
		i++;
	}
	j = 0;
	while (s2[j])
	{
		if (s2[j] == '\n')
			return (i + j + 1);
		j++;
	}
	return (i + j);
}

char	*ft_join(char *s1, char const *s2)
{
	char		*join;
	size_t		i;
	size_t		j;
	size_t		len;

	len = ft_strlens(s1, s2);
	join = malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (s1 && s1[i] && !(i > 0 && join[i - 1] == '\n') && i < len)
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] && !(j > 0 && join[i + j - 1] == '\n') && i + j < len)
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = 0;
	return (join);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_prev(char *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	if ((ft_strlen(s1) + ft_strlen(s2)) == 0)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = 0;
	if (s1)
		free(s1);
	return (join);
}

char	*freeall(char *line, char *buffer, char *prev)
{
	if (line)
		free(line);
	if (buffer)
		free(buffer);
	if (prev)
		free(prev);
	return (NULL);
}
