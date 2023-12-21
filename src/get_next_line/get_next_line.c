/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:16:33 by zwina             #+#    #+#             */
/*   Updated: 2021/11/19 09:06:13 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_new_line(const char *s)
{
	while (*s && *s != 10)
		s++;
	if (*s == 10)
		return ((char *)s);
	return (NULL);
}

void	ft_free_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

char	*get_line(char **holy_str, char **line)
{
	char	*new_holy_str;
	size_t	i;

	new_holy_str = NULL;
	i = 0;
	while ((*holy_str)[i] != 10 && (*holy_str)[i] != 0)
		i++;
	if ((*holy_str)[i] == 10)
	{
		*line = ft_substr(*holy_str, 0, ++i);
		new_holy_str = ft_strdup(*holy_str + i);
	}
	else
		*line = ft_strdup(*holy_str);
	ft_free_null(holy_str);
	if (**line == 0)
		ft_free_null(line);
	return (new_holy_str);
}

void	get_current_line(int fd, char **holy_str, char **line, char **buff)
{
	ssize_t	read_return;
	char	*tmp;

	read_return = 1;
	while (read_return && !ft_new_line(*holy_str))
	{
		read_return = read(fd, *buff, BUFFER_SIZE);
		(*buff)[read_return] = 0;
		tmp = *holy_str;
		*holy_str = ft_strjoin(tmp, *buff);
		ft_free_null(&tmp);
	}
	ft_free_null(buff);
	*holy_str = get_line(holy_str, line);
}

char	*get_next_line(int fd)
{
	static char	*holy_str;
	char		*line;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	if (read(fd, buff, 0) == -1)
	{
		ft_free_null(&buff);
		return (NULL);
	}
	if (!holy_str)
		holy_str = ft_strdup("");
	get_current_line(fd, &holy_str, &line, &buff);
	return (line);
}
