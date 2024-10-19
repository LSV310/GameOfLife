/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_of_life.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:03:32 by agruet            #+#    #+#             */
/*   Updated: 2024/09/10 15:58:51 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GAME_OF_LIFE
# define FT_GAME_OF_LIFE

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_point
{
	int	x;
	int	y;

}	t_point;

typedef struct s_cell
{
	int		state;
	t_point	coords;
}	t_cell;

int		contains_point(t_point *tab, int size, int x, int y);
int		contains_cell(t_cell *tab, int size, int x, int y);
int		verify_cell(t_cell calc, t_point *newtab, int new_size);
void	add_to_grid(char **g, int g_size, t_point *newtab, int new_size);
void	rem_from_grid(char **g, int g_size, t_point *newtab, int new_size);
void	verify_tab(t_cell *calc, int calc_size, t_point *newtab, int new_size, char **g, int g_size);
void	add_neighbors(t_point *newtab, int new_size, char **g, int g_size);
void	show_result(char **g, int g_size, t_point *newtab, int new_size);
void	create_grid(t_point *newtab, int new_size, int g_size);

#endif
