/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:45:09 by zwina             #+#    #+#             */
/*   Updated: 2022/03/05 11:10:11 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_in(t_point *point)
{
	point->x = ((WIDTH / (((5 * WIDTH) / 6) - (WIDTH / 6))) * \
				(point->x - (WIDTH / 6)));
	point->y = ((HEIGHT / (((5 * HEIGHT) / 6) - (HEIGHT / 6))) * \
				(point->y - (HEIGHT / 6)));
}

void	zoom_out(t_point *point)
{
	point->x = ((WIDTH / (((5 * WIDTH) / 4) + (WIDTH / 4))) * \
				(point->x + (WIDTH / 4)));
	point->y = ((HEIGHT / (((5 * HEIGHT) / 4) + (HEIGHT / 4))) * \
				(point->y + (HEIGHT / 4)));
}

void	color_scheme(t_fdf *fdf)
{
	fill_color(fdf);
	lets_draaaw(fdf);
}
