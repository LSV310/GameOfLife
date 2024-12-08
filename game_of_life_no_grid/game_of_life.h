/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_of_life.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:03:32 by agruet            #+#    #+#             */
/*   Updated: 2024/12/08 12:00:40 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_OF_LIFE
# define GAME_OF_LIFE

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <SDL2/SDL.h>
# include <math.h>

typedef struct s_cell
{
	int	state;
	int	x;
	int	y;
	int	lenght;
}	t_cell;

int		main(int ac, char **av);
void	free_tab(t_cell **tab, int size);
int		tab_contains_double(t_cell **tab, t_cell *new_content, int size);
int		contains_cell(t_cell **tab, int size, int x, int y);
int		verify_cell_gol(t_cell *calc, t_cell **newtab, int new_size);
int		verify_cell_hl(t_cell *calc, t_cell **newtab, int new_size);
t_cell	**verify_tab(t_cell **calc, int calc_size, t_cell **newtab, int new_size, int (*vc)(t_cell *, t_cell **, int));
t_cell	**add_neighbors(t_cell **newtab, int new_size, int game);
t_cell	**get_newtab(t_cell **tab, int new_size, int game);

#endif
