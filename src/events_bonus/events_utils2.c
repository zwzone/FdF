/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:57:31 by zwina             #+#    #+#             */
/*   Updated: 2022/03/05 13:43:02 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_back_center(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			map->map[i][j].x += WIDTH / 2;
			map->map[i][j].y += HEIGHT / 2;
			j++;
		}
		i++;
	}
}

void	rotate_z(t_point *point, double teta)
{
	float	current_x;
	float	current_y;
	float	current_z;

	current_x = point->x;
	current_y = point->y;
	current_z = point->z;
	point->x = current_x * cos(teta) - current_y * sin(teta);
	point->y = current_x * sin(teta) + current_y * cos(teta);
	point->z = current_z;
}

void	swap_point(t_point *p1, t_point *p2)
{
	t_point	tmp;

	tmp.x = p1->x;
	tmp.y = p1->y;
	tmp.z = p1->z;
	tmp.r = p1->r;
	tmp.g = p1->g;
	tmp.b = p1->b;
	tmp.color = p1->color;
	p1->x = p2->x;
	p1->y = p2->y;
	p1->z = p2->z;
	p1->r = p2->r;
	p1->g = p2->g;
	p1->b = p2->b;
	p1->color = p2->color;
	p2->x = tmp.x;
	p2->y = tmp.y;
	p2->z = tmp.z;
	p2->r = tmp.r;
	p2->g = tmp.g;
	p2->b = tmp.b;
	p2->color = tmp.color;
}

void	lets_rotate(t_fdf *fdf)
{
	size_t	i;
	size_t	j;

	set_2d_points(&fdf->data_map);
	set_to_center(&fdf->data_map);
	set_to_origin(&fdf->data_map);
	i = 0;
	while (i < fdf->data_map.row)
	{
		j = 0;
		while (j < fdf->data_map.column)
		{
			rotate_z(&fdf->data_map.map[i][j], fdf->data_map.teta);
			j++;
		}
		i++;
	}
	set_3d_points(&fdf->data_map);
	set_to_center(&fdf->data_map);
	lets_draaaw(fdf);
}
