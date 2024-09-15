/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:51:11 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/15 21:14:58 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	print_map(char **map)
// {
// 	size_t	i;

// 	i = 0;
// 	while (map && map[i])
// 	{
// 		printf("%s\n", map[i]);
// 		i++;
// 	}
// }

char	**lst_to_tab(t_list *lst)
{
	char	**tab;
	t_list	*tmp;
	int		i;

	tab = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	tmp = lst;
	while (lst)
	{
		tab[i] = ft_strtrim(lst->content, "\n");
		if (!tab[i])
		{
			free_tab(tab);
			return (NULL);
		}
		i++;
		lst = lst->next;
	}
	ft_lstclear(&tmp, free);
	tab[i] = NULL;
	return (tab);
}

char	**read_descriptor(char *file)
{
	t_list	*map;
	t_list	*temp;
	int		fd;
	char	*line;

	map = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		temp = ft_lstnew(line);
		if (!temp)
		{
			ft_lstclear(&map, free);
			return (NULL);
		}
		ft_lstadd_back(&map, temp);
		line = get_next_line(fd);
	}
	close(fd);
	return (lst_to_tab(map));
}

static int	error(char *err)
{
	ft_putstr_fd(err, 2);
	return (EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	char	**descriptor;
	t_data	*d;

	if (argc == 1)
		return (error("Error : No map\n"));
	descriptor = read_descriptor(argv[1]);
	if (!descriptor)
	{
		perror("Can't open the file: ");
		return (1);
	}
	d = init_data(descriptor);
	if (!d)
		return (1);
	if (is_map_valid(d->map, d) == FALSE)
	{
		free_data(d);
		return (error("Error : Invalid Map\n"));
	}
	loop(d);
	free_data(d);
	return (0);
}
