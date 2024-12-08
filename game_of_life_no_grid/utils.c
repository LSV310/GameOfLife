/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:37:42 by agruet            #+#    #+#             */
/*   Updated: 2024/12/08 12:12:50 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

void	free_tab(t_cell **tab, int size)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (i < size)
		free(tab[i++]);
	free(tab);
	tab = NULL;
}

int	contains_cell(t_cell **tab, int size, int x, int y)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i]->x == x && tab[i]->y == y)
			return (1);
		i++;
	}
	return (0);
}

int	tab_contains_double(t_cell **tab, t_cell *new_content, int size)
{
	if (!tab || !new_content)
		return (0);
	int	i = 0;
	while (i < size)
	{
		if (tab[i]->x == new_content->x
			&& tab[i]->y == new_content->y)
		{
			if (tab[i]->state == 0)
				tab[i]->state = 1;
			else
				tab[i]->state = 0;
			return (tab[i]->state + 1);
		}
		i++;
	}
	return (0);
}
