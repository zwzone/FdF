/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 09:03:27 by zwina             #+#    #+#             */
/*   Updated: 2022/03/05 15:47:17 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	draw_line_vars(t_point *middle, \
						t_point begin, t_point end, float *delta)
{
	float	pixels;

	delta[0] = end.x - begin.x;
	delta[1] = end.y - begin.y;
	delta[2] = end.z - begin.z;
	delta[3] = end.r - begin.r;
	delta[4] = end.g - begin.g;
	delta[5] = end.b - begin.b;
	pixels = sqrt((delta[0] * delta[0]) + (delta[1] * delta[1]));
	delta[0] /= pixels;
	delta[2] /= pixels;
	delta[3] /= pixels;
	delta[1] /= pixels;
	delta[4] /= pixels;
	delta[5] /= pixels;
	(*middle).x = begin.x;
	(*middle).y = begin.y;
	(*middle).z = begin.z;
	(*middle).r = begin.r;
	(*middle).g = begin.g;
	(*middle).b = begin.b;
	return (pixels);
}

void	draw_line(t_fdf fdf, t_point begin, t_point end)
{
	t_point	middle;
	float	delta[6];
	float	pixels;

	pixels = draw_line_vars(&middle, begin, end, delta);
	while (pixels-- > 0)
	{
		if (middle.x >= 0 && middle.x < WIDTH && \
			middle.y >= 0 && middle.y < HEIGHT)
			my_mlx_pixel_put(&fdf.data_img, middle.x, middle.y, \
							(int)(((int)middle.r << 16) + \
									((int)middle.g << 8) + \
									(int)middle.b));
		middle.x += delta[0];
		middle.y += delta[1];
		middle.z += delta[2];
		middle.r += delta[3];
		middle.g += delta[4];
		middle.b += delta[5];
	}
}

void	draw_map(t_fdf *fdf)
{
	size_t	i;
	size_t	j;

	fdf->data_img.img = mlx_new_image(fdf->mlx, fdf->width, fdf->height);
	fdf->data_img.addr = mlx_get_data_addr(fdf->data_img.img, \
										&fdf->data_img.bits_per_pixel, \
										&fdf->data_img.line_length, \
										&fdf->data_img.endian);
	i = -1;
	while (++i < fdf->data_map.row)
	{
		j = -1;
		while (++j < fdf->data_map.column)
		{
			if (j + 1 < fdf->data_map.column)
				draw_line(*fdf, fdf->data_map.map[i][j], \
					fdf->data_map.map[i][j + 1]);
			if (i + 1 < fdf->data_map.row)
				draw_line(*fdf, fdf->data_map.map[i][j], \
					fdf->data_map.map[i + 1][j]);
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->data_img.img, 0, 0);
	mlx_destroy_image(fdf->mlx, fdf->data_img.img);
}

void	draw_map_reverse(t_fdf *fdf)
{
	size_t	i;
	size_t	j;

	fdf->data_img.img = mlx_new_image(fdf->mlx, fdf->width, fdf->height);
	fdf->data_img.addr = mlx_get_data_addr(fdf->data_img.img, \
		&fdf->data_img.bits_per_pixel, &fdf->data_img.line_length, \
										&fdf->data_img.endian);
	i = fdf->data_map.row;
	while (i > 0)
	{
		i--;
		j = fdf->data_map.column;
		while (j > 0)
		{
			j--;
			if (j + 1 < fdf->data_map.column)
				draw_line(*fdf, fdf->data_map.map[i][j], \
					fdf->data_map.map[i][j + 1]);
			if (i + 1 < fdf->data_map.row)
				draw_line(*fdf, fdf->data_map.map[i][j], \
					fdf->data_map.map[i + 1][j]);
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->data_img.img, 0, 0);
	mlx_destroy_image(fdf->mlx, fdf->data_img.img);
}

void	lets_draaaw(t_fdf *fdf)
{
	if ((fdf->data_map.teta > M_PI_4 && fdf->data_map.teta <= M_PI_4 * 5) || \
		(fdf->data_map.teta <= M_PI_4 * -3 && fdf->data_map.teta > M_PI_4 * -7))
		draw_map_reverse(fdf);
	else
		draw_map(fdf);
}
