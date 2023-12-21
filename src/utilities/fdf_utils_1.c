/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:05:20 by zwina             #+#    #+#             */
/*   Updated: 2022/03/05 11:05:57 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	free_list(t_list *my_list)
{
	t_list	*tmp;

	while (my_list)
	{
		if ((char *)my_list->content)
			free((char *)my_list->content);
		tmp = my_list;
		my_list = my_list->next;
		free(tmp);
	}
}

size_t	width_of_map(t_point **map)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = 0;
	while (map[0][len].color != -2.0f)
		len++;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j].color != -2.0f)
			j++;
		if (len != j)
			ft_error(MINR, 0);
		i++;
	}
	return (len);
}

size_t	height_of_map(t_point **map)
{
	size_t	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
