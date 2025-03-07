/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:22:36 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/19 17:39:11 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**ft_deep_copy_tab(char **tab)
{
	char	**copy;
	size_t	i;

	if (!tab)
		return (NULL);
	copy = ft_calloc(size_tab(tab) + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (tab && tab[i])
	{
		copy[i] = ft_strdup(tab[i]);
		if (!copy[i])
		{
			free_tab(copy);
			ft_putstr_fd("Error : No memory\n", 2);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

size_t	size_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**clean_tab(char **tab)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (tab && tab[i])
	{
		tmp = ft_strtrim(tab[i], " \n\t\v\r\f");
		if (!tmp)
		{
			free_tab(tab);
			return (NULL);
		}
		free(tab[i]);
		tab[i] = tmp;
		i++;
	}
	return (tab);
}
