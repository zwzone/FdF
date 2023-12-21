/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fdf_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 09:05:00 by zwina             #+#    #+#             */
/*   Updated: 2023/12/21 11:53:37 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void print_help_message(void)
{
	ft_putendl_fd("\n\t\t==>> HELP <<==\n", 1);
	ft_putendl_fd("\tPress { ESC } to exit.", 1);
	ft_putendl_fd("\tPress { P } to change the projection.", 1);
	ft_putendl_fd(
			"\tPress { w/(up), a/(left), s/(down), d/(right) } to translate.", 1);
	ft_putendl_fd("\tPress { -, + } to zoom.", 1);
	ft_putendl_fd("\tPress { [, ] } to rotate.", 1);
	ft_putendl_fd("\tPress { <, > } to scale Z axis.", 1);
	ft_putendl_fd("\tPress { C } to change the color scheme.\n", 1);
}

int close_win(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit(0);
	return (0);
}

int events(int keycode, t_fdf *fdf)
{
	printf("%d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		exit(0);
	}
	else if (keycode == 35)
		projection_converter(fdf);
	else if (keycode == 0 || keycode == 1 || keycode == 2 || keycode == 13 ||
					 keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
		translate(keycode, fdf);
	else if (keycode == 24 || keycode == 27)
		zooming(keycode, fdf);
	else if (keycode == 43 || keycode == 47)
		scaling_z(keycode, fdf);
	else if (keycode == 8)
		color_scheme(fdf);
	else if (keycode == 30 || keycode == 33)
		rotation(keycode, fdf);
	return (0);
}

void run_fdf(t_fdf *fdf)
{
	fdf->height = HEIGHT;
	fdf->width = WIDTH;
	print_help_message();
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, fdf->width, fdf->height, "FDF");
	lets_draaaw(fdf);
	mlx_key_hook(fdf->win, events, fdf);
	// mlx_hook(fdf->win, 2, 0L, events, fdf);
	mlx_hook(fdf->win, 17, 0L, close_win, fdf);
	mlx_loop(fdf->mlx);
}
