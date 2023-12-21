/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:03:16 by zwina             #+#    #+#             */
/*   Updated: 2022/02/26 12:07:29 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	strslen(char **strs)
{
	int	count;

	count = 0;
	while (strs[count])
		count++;
	return (count);
}

t_point	*allocate_line(int len)
{
	t_point	*line;

	line = (t_point *)malloc(sizeof(t_point) * (len + 1));
	if (!line)
		ft_error(0, "malloc");
	return (line);
}

t_point	*line_of_map(char **strs)
{
	t_point	*line;
	char	**z_and_color;
	int		len;
	int		i;

	len = strslen(strs);
	line = allocate_line(len);
	i = 0;
	while (i < len)
	{
		z_and_color = ft_split(strs[i], ',');
		if (!z_and_color)
			ft_error(0, "split");
		line[i].z = (float)ft_atoi(z_and_color[0]) * 2;
		line[i].color = (float)ft_atoi_16(z_and_color[1]);
		free_strs(z_and_color);
		i++;
	}
	line[i].color = -2.0f;
	return (line);
}

t_point	**strmap_to_intmap(t_list *lines)
{
	t_point	**map;
	t_list	*tmp;
	char	**strs;
	int		rows;
	int		i;

	tmp = lines;
	rows = ft_lstsize(lines);
	map = (t_point **)malloc(sizeof(t_point *) * (rows + 1));
	if (!map)
		ft_error(0, "malloc");
	i = 0;
	while (tmp && i < rows)
	{
		strs = ft_split((char *)tmp->content, ' ');
		if (!strs)
			ft_error(0, "ft_split");
		map[i] = line_of_map(strs);
		free_strs(strs);
		tmp = tmp->next;
		i++;
	}
	map[i] = NULL;
	free_list(lines);
	return (map);
}

t_point	**get_map(char *path)
{
	t_list	*lines;
	t_list	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error(0, path);
	lines = NULL;
	line = ft_lstnew(get_next_line(fd));
	if (!line)
		ft_error(0, "ft_lstnew");
	if (!(char *)line->content)
		ft_error(FISE, 0);
	while ((char *)line->content)
	{
		ft_lstadd_back(&lines, line);
		line = ft_lstnew(get_next_line(fd));
		if (!line)
			ft_error(0, "ft_lstnew");
	}
	close(fd);
	free(line);
	return (strmap_to_intmap(lines));
}
