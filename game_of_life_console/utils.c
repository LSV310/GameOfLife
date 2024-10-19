/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:37:42 by agruet            #+#    #+#             */
/*   Updated: 2024/09/10 15:21:44 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

int	contains_point(t_point *tab, int size, int x, int y)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i].x == x && tab[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

int	contains_cell(t_cell *tab, int size, int x, int y)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i].coords.x == x && tab[i].coords.y == y)
			return (1);
		i++;
	}
	return (0);
}
