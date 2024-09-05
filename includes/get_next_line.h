/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:20:01 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/05 16:20:39 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//gnl_utils
size_t	ft_strlens(const char *s1, const char *s2);
char	*ft_join(char *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strjoin_prev(char *s1, char const *s2);
char	*freeall(char *line, char *buffer, char *prev);
//char	*setprev(char *prev, char buffer[]);
//gnl
int		checkline(char	*line);
char	*ft_strdup(const char *s);
char	*removeline(char *prev, char *line, char *buffer);
char	*setline(char *line, char *prev, char *buffer);
char	*get_next_line(int fd);

#endif
