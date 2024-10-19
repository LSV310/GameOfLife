/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cells.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:44:19 by agruet            #+#    #+#             */
/*   Updated: 2024/09/10 15:24:01 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

void	add_cell(t_cell *calc, int x, int y, int *i, t_point *newtab, int new_size, int g_size)
{
	if (!contains_cell(calc, *i, x, y)
		&& x >= -g_size && x <= g_size
		&& y >= -g_size && y <= g_size)
	{
		calc[*i].state = contains_point(newtab, new_size, x, y);
		calc[*i].coords.x = x;
		calc[(*i)++].coords.y = y;
	}
}

void	add_neighbors(t_point *newtab, int new_size, char **g, int g_size)
{
	int		i;
	int		j;
	t_cell	*calc;

	calc = malloc(sizeof(t_cell) * (new_size * 9));
	if (!calc)
		return ;
	i = 0;
	j = 0;
	while (i < new_size)
	{
		add_cell(calc, newtab[i].x, newtab[i].y, &j, newtab, new_size, g_size);
		add_cell(calc, newtab[i].x + 1, newtab[i].y, &j, newtab, new_size, g_size);
		add_cell(calc, newtab[i].x, newtab[i].y + 1, &j, newtab, new_size, g_size);
		add_cell(calc, newtab[i].x + 1, newtab[i].y + 1, &j, newtab, new_size, g_size);
		add_cell(calc, newtab[i].x - 1, newtab[i].y, &j, newtab, new_size, g_size);
		add_cell(calc, newtab[i].x, newtab[i].y - 1, &j, newtab, new_size, g_size);
		add_cell(calc, newtab[i].x - 1, newtab[i].y - 1, &j, newtab, new_size, g_size);
		add_cell(calc, newtab[i].x + 1, newtab[i].y - 1, &j, newtab, new_size, g_size);
		add_cell(calc, newtab[i].x - 1, newtab[i].y + 1, &j, newtab, new_size, g_size);
		i++;
	}
	verify_tab(calc, j, newtab, new_size, g, g_size);
}

int	neighbor_count(t_point *newtab, int size, int x, int y)
{
	int	i;

	i = 0;
	if (contains_point(newtab, size, x + 1, y))
		i++;
	if (contains_point(newtab, size, x, y + 1))
		i++;
	if (contains_point(newtab, size, x + 1, y + 1))
		i++;
	if (contains_point(newtab, size, x - 1, y))
		i++;
	if (contains_point(newtab, size, x, y - 1))
		i++;
	if (contains_point(newtab, size, x - 1, y - 1))
		i++;
	if (contains_point(newtab, size, x + 1, y - 1))
		i++;
	if (contains_point(newtab, size, x - 1, y + 1))
		i++;
	return (i);
}

int	verify_cell(t_cell calc, t_point *newtab, int new_size)
{
	int	count;

	count = neighbor_count(newtab, new_size, calc.coords.x, calc.coords.y);
	if (count == 3)
		return (1);
	if (count == 2)
		return (calc.state);
	if (count < 2 || count > 3)
		return (0);
	return (0);
}
