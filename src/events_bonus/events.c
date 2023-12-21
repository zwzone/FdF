/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:03:11 by zwina             #+#    #+#             */
/*   Updated: 2022/03/05 15:52:45 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate(int keycode, t_fdf *fdf)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < fdf->data_map.row)
	{
		j = 0;
		while (j < fdf->data_map.column)
		{
			if (keycode == 13 || keycode == 126)
				fdf->data_map.map[i][j].y -= 10 * (fdf->data_map.zoom);
			else if (keycode == 0 || keycode == 123)
				fdf->data_map.map[i][j].x -= 10 * (fdf->data_map.zoom);
			else if (keycode == 1 || keycode == 125)
				fdf->data_map.map[i][j].y += 10 * (fdf->data_map.zoom);
			else if (keycode == 2 || keycode == 124)
				fdf->data_map.map[i][j].x += 10 * (fdf->data_map.zoom);
			j++;
		}
		i++;
	}
	lets_draaaw(fdf);
}

void	zooming(int keycode, t_fdf *fdf)
{
	size_t	i;
	size_t	j;

	if ((keycode == 24 && fdf->data_map.zoom >= (float)(1.5 * 2)) || \
		(keycode == 27 && fdf->data_map.zoom <= (float)(1.5 / 4)))
		return ;
	i = -1;
	while (++i < fdf->data_map.row)
	{
		j = -1;
		while (++j < fdf->data_map.column)
		{
			if (keycode == 24)
				zoom_in(&fdf->data_map.map[i][j]);
			else if (keycode == 27)
				zoom_out(&fdf->data_map.map[i][j]);
		}
	}
	if (keycode == 24)
		fdf->data_map.zoom *= 1.5;
	else if (keycode == 27)
		fdf->data_map.zoom /= 1.5;
	lets_draaaw(fdf);
}

void	projection_converter(t_fdf *fdf)
{
	fdf->data_map.zoom = 1;
	fdf->data_map.z_scaler = 0;
	set_2d_points(&fdf->data_map);
	if (fdf->data_map.projection == 1)
	{
		fdf->data_map.projection = 0;
		fdf->data_map.teta = 0;
	}
	else if (fdf->data_map.projection == 0)
	{
		set_3d_points(&fdf->data_map);
		fdf->data_map.projection = 1;
	}
	set_to_center(&fdf->data_map);
	lets_draaaw(fdf);
}

void	scaling_z(int keycode, t_fdf *fdf)
{
	size_t	i;
	size_t	j;

	if ((fdf->data_map.projection == 0) || (keycode == 47 && fdf->data_map.\
	z_scaler >= 6) || (keycode == 43 && fdf->data_map.z_scaler <= -14))
		return ;
	i = -1;
	while (++i < fdf->data_map.row)
	{
		j = -1;
		while (++j < fdf->data_map.column)
		{
			if (keycode == 43)
				fdf->data_map.map[i][j].y += \
					(fdf->data_map.map[i][j].z * fdf->data_map.zoom) / 4;
			if (keycode == 47)
				fdf->data_map.map[i][j].y -= \
					(fdf->data_map.map[i][j].z * fdf->data_map.zoom) / 4;
		}
	}
	if (keycode == 47)
		fdf->data_map.z_scaler += 1;
	else if (keycode == 43)
		fdf->data_map.z_scaler -= 1;
	lets_draaaw(fdf);
}

void	rotation(int keycode, t_fdf *fdf)
{
	if (fdf->data_map.projection == 0)
		return ;
	fdf->data_map.z_scaler = 0;
	fdf->data_map.zoom = 1;
	if (fdf->data_map.teta >= M_PI * 2 || fdf->data_map.teta <= M_PI * -2)
		fdf->data_map.teta = 0;
	if (keycode == 30)
		fdf->data_map.teta += M_PI_4 / 2;
	else if (keycode == 33)
		fdf->data_map.teta -= M_PI_4 / 2;
	lets_rotate(fdf);
}
