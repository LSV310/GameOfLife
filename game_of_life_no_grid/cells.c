/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cells.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:44:19 by agruet            #+#    #+#             */
/*   Updated: 2025/01/05 17:20:04 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

void	add_cell(t_cell **calc, int x, int y, int *i, t_cell **newtab, int new_size)
{
	if (!contains_cell(calc, *i, x, y))
	{
		t_cell	*new_cell;

		new_cell = malloc(sizeof(t_cell));
		if (!new_cell)
			return ;
		new_cell->state = contains_cell(newtab, new_size, x, y);
		new_cell->x = x;
		new_cell->y = y;
		calc[(*i)++] = new_cell;
	}
}

t_cell	**add_neighbors(t_cell **newtab, int new_size, int game)
{
	int		i;
	int		j;
	t_cell	**calc;

	calc = malloc(sizeof(t_cell *) * (new_size * 9));
	if (!calc)
	{
		free_tab(newtab, new_size);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (i < new_size)
	{
		add_cell(calc, newtab[i]->x, newtab[i]->y, &j, newtab, new_size);
		add_cell(calc, newtab[i]->x + 1, newtab[i]->y, &j, newtab, new_size);
		add_cell(calc, newtab[i]->x, newtab[i]->y + 1, &j, newtab, new_size);
		add_cell(calc, newtab[i]->x + 1, newtab[i]->y + 1, &j, newtab, new_size);
		add_cell(calc, newtab[i]->x - 1, newtab[i]->y, &j, newtab, new_size);
		add_cell(calc, newtab[i]->x, newtab[i]->y - 1, &j, newtab, new_size);
		add_cell(calc, newtab[i]->x - 1, newtab[i]->y - 1, &j, newtab, new_size);
		add_cell(calc, newtab[i]->x + 1, newtab[i]->y - 1, &j, newtab, new_size);
		add_cell(calc, newtab[i]->x - 1, newtab[i]->y + 1, &j, newtab, new_size);
		i++;
	}
	if (game == 0)
		return (verify_tab(calc, j, newtab, new_size, &verify_cell_gol));
	else
		return (verify_tab(calc, j, newtab, new_size, &verify_cell_hl));
}

int	neighbor_count(t_cell **newtab, int size, int x, int y)
{
	int	i;

	i = 0;
	if (contains_cell(newtab, size, x + 1, y))
		i++;
	if (contains_cell(newtab, size, x, y + 1))
		i++;
	if (contains_cell(newtab, size, x + 1, y + 1))
		i++;
	if (contains_cell(newtab, size, x - 1, y))
		i++;
	if (contains_cell(newtab, size, x, y - 1))
		i++;
	if (contains_cell(newtab, size, x - 1, y - 1))
		i++;
	if (contains_cell(newtab, size, x + 1, y - 1))
		i++;
	if (contains_cell(newtab, size, x - 1, y + 1))
		i++;
	return (i);
}

// Function for the Game Of Life
int	verify_cell_gol(t_cell *calc, t_cell **newtab, int new_size)
{
	int	count;

	count = neighbor_count(newtab, new_size, calc->x, calc->y);
	if (count == 3)
		return (1);
	if (count == 2)
		return (calc->state);
	if (count < 2 || count > 3)
		return (0);
	return (0);
}

// Function for High Life
int	verify_cell_hl(t_cell *calc, t_cell **newtab, int new_size)
{
	int	count;

	count = neighbor_count(newtab, new_size, calc->x, calc->y);
	if (count == 3 || (count == 6 && calc->state == 0))
		return (1);
	else if (count == 2)
		return (calc->state);
	else
		return (0);
}
