/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:37:40 by agruet            #+#    #+#             */
/*   Updated: 2024/09/10 23:09:47 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

void	fill_grid(char **g, int g_size)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < g_size)
	{
		y = 0;
		g[x] = malloc(sizeof(char) * (g_size + 1));
		if (!g[x])
			return ;
		while (y < g_size)
		{
			g[x][y++] = ' ';
		}
		g[x++][y] = 0;
	}
	g[x] = 0;
}

void	free_grid(char **g, int g_size)
{
	int	i;

	i = 0;
	while (i < g_size)
		free(g[i++]);
	free(g);
}

void	add_to_grid(char **g, int g_size, t_point *newtab, int new_size)
{
	int	i;

	i = 0;
	while (i < new_size)
	{
		if (newtab[i].x >= -g_size / 2 && newtab[i].x <= g_size / 2
			&& newtab[i].y >= -g_size / 2 && newtab[i].y <= g_size / 2)
			g[newtab[i].y + g_size / 2][newtab[i].x + g_size / 2] = 'o';
		i++;
	}
}

void	rem_from_grid(char **g, int g_size, t_point *newtab, int new_size)
{
	int	i;

	i = 0;
	while (i < new_size)
	{
		if (newtab[i].x >= -g_size / 2 && newtab[i].x <= g_size / 2
			&& newtab[i].y >= -g_size / 2 && newtab[i].y <= g_size / 2)
			g[newtab[i].y + g_size / 2][newtab[i].x + g_size / 2] = ' ';
		i++;
	}
}

void	create_grid(t_point *newtab, int new_size, int g_size)
{
	char	**g;

	g = malloc(sizeof(char *) * (g_size + 1));
	if (!g)
		return ;
	fill_grid(g, g_size);
	show_result(g, g_size, newtab, new_size);
	free_grid(g, g_size);
}
