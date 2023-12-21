/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:43:39 by zwina             #+#    #+#             */
/*   Updated: 2022/03/05 15:34:00 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(int nerr, char *str)
{
	ft_putstr_fd("fdf: ", 2);
	if (nerr == WNOA)
		ft_putendl_fd("wrong number of arguments.", 2);
	else if (nerr == FERR)
		ft_putendl_fd("the format of the file is not right.", 2);
	else if (nerr == FISE)
		ft_putendl_fd("the file is empty.", 2);
	else if (nerr == MINR)
		ft_putendl_fd("the map is not rectangular.", 2);
	else
		perror(str);
	ft_putendl_fd("help >> \"./fdf \'*.fdf\'\"", 2);
	exit(1);
}

void	check_arguments(int ac, char **av)
{
	int	len;

	if (ac != 2)
		ft_error(WNOA, 0);
	len = ft_strlen(av[1]);
	if (len < 5 || ft_strncmp(av[1] + len - 4, ".fdf", 5))
		ft_error(FERR, 0);
}
