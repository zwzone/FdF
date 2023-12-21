/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:02:50 by zwina             #+#    #+#             */
/*   Updated: 2023/12/21 11:37:42 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <errno.h>
# define WNOA -1
# define FERR -2
# define FISE -3
# define MINR -4
# define WIDTH 1920.0f
# define HEIGHT 1080.0f

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	float	r;
	float	g;
	float	b;
	float	color;
}			t_point;

typedef struct s_map
{
	t_point	**map;
	float	max_z;
	float	min_z;
	float	z_scaler;
	float	zoom;
	char	color_scheme;
	char	projection;
	double	teta;
	size_t	row;
	size_t	column;
}			t_map;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	size_t	height;
	size_t	width;
	t_map	data_map;
	t_data	data_img;
}			t_fdf;

// ---<<< Error Functions >>>---
void	ft_error(int nerr, char *str);
void	check_arguments(int ac, char **av);

// ---<<< Utilities >>>---
void	free_strs(char **strs);
void	free_list(t_list *my_list);
size_t	height_of_map(t_point **map);
size_t	width_of_map(t_point **map);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
float	max_z_map(t_map map);
float	min_z_map(t_map map);
void	fill_color(t_fdf *fdf);

// ---<<< Getting Data Of The Map >>>---
t_point	**get_map(char *path);
void	set_to_center(t_map *map);
void	set_to_origin(t_map *map);
void	set_2d_points(t_map *map);
void	set_3d_points(t_map *map);
t_fdf	*setup_map(char *filename);

// ---<<< Drawing Functions >>>---
void	lets_draaaw(t_fdf *fdf);
void	run_fdf(t_fdf *fdf);

// ---<<< Events >>>---
// closing
int		close_win(t_fdf *fdf);
// translating
void	translate(int keycode, t_fdf *fdf);
// zooming
void	zoom_in(t_point *point);
void	zoom_out(t_point *point);
void	zooming(int keycode, t_fdf *fdf);
// coloring
void	color_scheme(t_fdf *fdf);
// scaling the z axis
void	scaling_z(int keycode, t_fdf *fdf);
// converting the projection
void	projection_converter(t_fdf *fdf);
// rotating
void	rotate_z(t_point *point, double teta);
void	lets_rotate(t_fdf *fdf);
void	rotation(int keycode, t_fdf *fdf);
int		events(int keycode, t_fdf *fdf);

#endif
