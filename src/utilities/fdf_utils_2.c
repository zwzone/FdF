/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:01:19 by zwina             #+#    #+#             */
/*   Updated: 2022/03/05 14:13:15 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	max_z_map(t_map map)
{
	float	max;
	size_t	i;
	size_t	j;

	max = map.map[0][0].z;
	i = 0;
	while (i < map.row)
	{
		j = 0;
		while (j < map.column)
		{
			if (max <= map.map[i][j].z)
				max = map.map[i][j].z;
			j++;
		}
		i++;
	}
	return (max);
}

float	min_z_map(t_map map)
{
	float	min;
	size_t	i;
	size_t	j;

	min = map.map[0][0].z;
	i = 0;
	while (i < map.row)
	{
		j = 0;
		while (j < map.column)
		{
			if (min >= map.map[i][j].z)
				min = map.map[i][j].z;
			j++;
		}
		i++;
	}
	return (min);
}

static float	get_color(char color_scheme, float z, float max, float min)
{
	float	color;

	if (color_scheme == 1)
		color = ((int)((0xff / (max - min)) * (z - min)) << 8) + 0xff0000;
	if (color_scheme == 2)
		color = ((int)((0xff / (max - min)) * (z - min))) + 0xff00;
	if (color_scheme == 3)
		color = ((int)((0xff / (max - min)) * (z - min)) << 16) + 0xff;
	if (color_scheme == 4)
		color = ((int)((0xff / (max - min)) * (z - min)) << 8) + 0xff;
	if (color_scheme == 5)
		color = ((int)((0xff / (max - min)) * (z - min))) + 0xff0000;
	if (color_scheme == 6)
		color = ((int)((0xff / (max - min)) * (z - min)) << 16) + 0xff00;
	if (color_scheme == 7)
		color = ((int)((0xff / (max - min)) * (z - min)) << 8) + 0xff00ff;
	if (color_scheme == 8)
		color = ((int)((0xff / (max - min)) * (z - min))) + 0xffff00;
	if (color_scheme == 9)
		color = ((int)((0xff / (max - min)) * (z - min)) << 16) + 0xffff;
	if (color_scheme == 10)
		color = (int)((0xff / (max - min)) * (z - min)) << 8;
	return (color);
}

static void	fill_rgb(t_point *point, float max, float min, char color_scheme)
{
	float	color;

	if (point->color == -1)
	{
		color = get_color(color_scheme, point->z, max, min);
		point->r = (int)(color / 0x10000) % 0x100;
		point->g = (int)(color / 0x100) % 0x100;
		point->b = (int)color % 0x100;
	}
	else
	{
		point->r = (int)(point->color / 0x10000) % 0x100;
		point->g = (int)(point->color / 0x100) % 0x100;
		point->b = (int)point->color % 0x100;
	}
}

void	fill_color(t_fdf *fdf)
{
	size_t	i;
	size_t	j;

	fdf->data_map.color_scheme++;
	if (fdf->data_map.color_scheme > 10)
		fdf->data_map.color_scheme = 1;
	i = 0;
	while (i < fdf->data_map.row)
	{
		j = 0;
		while (j < fdf->data_map.column)
		{
			fill_rgb(&fdf->data_map.map[i][j], fdf->data_map.max_z, \
					fdf->data_map.min_z, fdf->data_map.color_scheme);
			j++;
		}
		i++;
	}
}
