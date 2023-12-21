/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:47:46 by zwina             #+#    #+#             */
/*   Updated: 2022/03/05 13:41:51 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_2d_points(t_map *map)
{
	float	delta_map;
	size_t	i;
	size_t	j;

	if (map->row < map->column)
		delta_map = (float)((float)HEIGHT / (float)map->column);
	else
		delta_map = (float)((float)HEIGHT / (float)map->row);
	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			map->map[i][j].x = (float)(delta_map * (float)j);
			map->map[i][j].y = (float)(delta_map * (float)i);
			j++;
		}
		i++;
	}
}

void	set_3d_points(t_map *map)
{
	float	current_x;
	float	current_y;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			current_x = map->map[i][j].x;
			current_y = map->map[i][j].y;
			map->map[i][j].x = (float)((current_x - current_y) / 1.5);
			map->map[i][j].y = (float)((current_x + current_y) / 2.5 - \
										map->map[i][j].z);
			j++;
		}
		i++;
	}
}

void	set_to_origin(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			map->map[i][j].x -= WIDTH / 2;
			map->map[i][j].y -= HEIGHT / 2;
			j++;
		}
		i++;
	}
}

void	set_to_center(t_map *map)
{
	float	delay_x;
	float	delay_y;
	size_t	i;
	size_t	j;

	delay_x = (WIDTH - (map->map[0][map->column - 1].x - \
							map->map[map->row - 1][0].x)) / \
							2 - map->map[map->row - 1][0].x;
	delay_y = (HEIGHT - (map->map[map->row - 1][map->column - 1].y - \
							map->map[0][0].y)) / \
							2 - map->map[0][0].y;
	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			map->map[i][j].x += delay_x;
			map->map[i][j].y += delay_y;
			j++;
		}
		i++;
	}
}

t_fdf	*setup_map(char *filename)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		ft_error(0, "malloc");
	fdf->data_map.zoom = 1;
	fdf->data_map.projection = 1;
	fdf->data_map.color_scheme = 0;
	fdf->data_map.z_scaler = 0;
	fdf->data_map.teta = 0;
	fdf->data_map.map = get_map(filename);
	fdf->data_map.row = height_of_map(fdf->data_map.map);
	fdf->data_map.column = width_of_map(fdf->data_map.map);
	fdf->data_map.max_z = max_z_map(fdf->data_map);
	fdf->data_map.min_z = min_z_map(fdf->data_map);
	set_2d_points(&fdf->data_map);
	set_3d_points(&fdf->data_map);
	set_to_center(&fdf->data_map);
	fill_color(fdf);
	return (fdf);
}
