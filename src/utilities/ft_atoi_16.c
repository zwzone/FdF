/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 09:27:53 by zwina             #+#    #+#             */
/*   Updated: 2022/02/23 13:23:23 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	set_var(char **str, int *n, int *i)
{
	*str = *str + 2;
	*n = 0;
	*i = -1;
}

int	ft_atoi_16(char *str)
{
	int		i;
	int		j;
	int		n;
	char	*base_low;
	char	*base_up;

	base_low = "0123456789abcdef";
	base_up = "0123456789ABCDEF";
	if (!str)
		return (-1);
	set_var(&str, &n, &i);
	while (str[++i])
	{
		j = -1;
		while (base_low[++j])
		{
			if (base_low[j] == str[i] || base_up[j] == str[i])
				break ;
		}
		if (!base_low[j])
			return (n);
		n = (n * 16) + j;
	}
	return (n);
}
