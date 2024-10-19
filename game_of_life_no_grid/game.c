/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:32:36 by marvin            #+#    #+#             */
/*   Updated: 2024/09/07 11:32:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

int	fill_result(t_cell **result, t_cell **calc, int calc_size, t_cell **newtab, int new_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < calc_size)
	{
		if (verify_cell(calc[i], newtab, new_size))
		{
			t_cell	*new_cell;
			new_cell = malloc(sizeof(t_cell));
			if (!new_cell)
				return (0);
			new_cell->state = 1;
			new_cell->x = calc[i]->x;
			new_cell->y = calc[i]->y;
			new_cell->lenght = new_size;
			result[j++] = new_cell;
		}
		i++;
	}
	result[0]->lenght = j;
	return (j);
}

t_cell	**verify_tab(t_cell **calc, int calc_size, t_cell **newtab, int new_size)
{
	int		i;
	int		count;
	t_cell	**result;
	int		res_size;

	i = 0;
	count = 0;
	while (i < calc_size)
		count += verify_cell(calc[i++], newtab, new_size);
	result = malloc(sizeof(t_cell *) * (count));
	if (!result || !count)
	{
		if (!count)
			free(result);
		free_tab(newtab, new_size);
		free_tab(calc, calc_size);
		return (NULL);
	}
	res_size = fill_result(result, calc, calc_size, newtab, new_size);
	free_tab(calc, calc_size);
	free_tab(newtab, new_size);
	if (res_size)
		return (result);
	free_tab(result, count);
	return (NULL);
}

t_cell	**get_newtab(t_cell **tab, int new_size)
{
	t_cell	**newtab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < new_size)
	{
		if (tab[j++]->state == 1)
			i++;
	}
	newtab = malloc(sizeof(t_cell *) * i);
	if (!newtab)
		return (NULL);
	i = 0;
	j = 0;
	while (j < new_size)
	{
		if (tab[j]->state == 1)
			newtab[i++] = tab[j];
		else
			free(tab[j]);
		j++;
	}
	return (add_neighbors(newtab, i));
}
