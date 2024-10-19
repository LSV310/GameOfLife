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

int	fill_result(t_point *result, t_cell *calc, int calc_size, t_point *newtab, int new_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < calc_size)
	{
		if (verify_cell(calc[i], newtab, new_size))
		{
			result[j].x = calc[i].coords.x;
			result[j++].y = calc[i].coords.y;
		}
		i++;
	}
	free(calc);
	return (j);
}

void	verify_tab(t_cell *calc, int calc_size, t_point *newtab, int new_size, char **g, int g_size)
{
	int		i;
	int		count;
	t_point	*result;
	int		res_size;

	i = 0;
	count = 0;
	while (i < calc_size)
		count += verify_cell(calc[i++], newtab, new_size);
	result = malloc(sizeof(t_point) * (count));
	if (!result)
		return ;
	res_size = fill_result(result, calc, calc_size, newtab, new_size);
	free(newtab);
	if (res_size)
		show_result(g, g_size, result, res_size);
	else
		free(result);
}

void	show_result(char **g, int g_size, t_point *newtab, int new_size)
{
	int			i;
	int			j;
	// static int	gen;

	add_to_grid(g, g_size, newtab, new_size);
	i = g_size;
	while (--i >= 0)
	{
		j = 0;
		while (j < g_size)
			printf("%c ", g[i][j++]);
		printf("\n");
	}
	rem_from_grid(g, g_size, newtab, new_size);
	// usleep(300 * 1000);
	/* if (gen++ == 20)
	{
		free(newtab);
		return ;
	} */
	add_neighbors(newtab, new_size, g, g_size);
}

int	main(int ac, char **av)
{
	t_point	*tab;
	int		i;
	int		j;

	if (ac < 2 || ac % 2 != 0 || atoi(av[1]) % 2 != 0)
		return (-1);
	tab = malloc(sizeof(t_point) * ((ac - 2) / 2));
	if (!tab)
		return (-1);
	i = 0;
	j = 2;
	while (av[j])
	{
		tab[i].x = atoi(av[j++]);
		tab[i++].y = atoi(av[j++]);
	}
	create_grid(tab, (ac - 2) / 2, atoi(av[1]) * 2 + 1);
	return (0);
}
