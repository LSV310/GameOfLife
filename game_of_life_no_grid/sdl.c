/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:48:31 by agruet            #+#    #+#             */
/*   Updated: 2024/10/19 10:26:59 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

#define INITIAL_CELL_SIZE 20

void	draw_grid(SDL_Renderer *renderer, int window_width, int window_height, float cell_size, float offset_x, float offset_y)
{
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, SDL_ALPHA_OPAQUE);

	for (float y = fmodf(offset_y, cell_size); y <= window_height; y += cell_size) {
		SDL_RenderDrawLine(renderer, 0, y, window_width, y);
	}

	for (float x = fmodf(offset_x, cell_size); x <= window_width; x += cell_size) {
		SDL_RenderDrawLine(renderer, x, 0, x, window_height);
	}
}

void	draw_cell(SDL_Renderer *renderer, t_cell *cell, float cell_size, float offset_x, float offset_y) {
	if (cell->state == 1) {
		SDL_Rect rect;
		rect.x = (cell->x * cell_size) + offset_x;
		rect.y = (cell->y * cell_size) + offset_y;
		rect.w = cell_size + 1;  // Taille de la cellule vivante
		rect.h = cell_size + 1;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &rect);
	}
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	int	sdl = SDL_Init(SDL_INIT_VIDEO);
	if (sdl) {
		printf("Erreur SDL_Init: %s\n", SDL_GetError());
		return (1);
	}

	int window_width = 800, window_height = 600;

	SDL_Window *window = SDL_CreateWindow("Jeu de la vie",
									SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
									window_width, window_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
	if (!window) {
		printf("Erreur SDL_CreateWindow: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("Erreur SDL_CreateRenderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}

	// Variables pour le zoom et le pan
	float cell_size = INITIAL_CELL_SIZE;
	float offset_x = 0, offset_y = 0; // Décalage pour le pan
	int mouse_pan = 0; // Déplacement activé par clic gauche maintenu
	int last_mouse_x = 0, last_mouse_y = 0; // Dernière position de la souris

	t_cell	**tab;
	tab = malloc(sizeof(t_cell *) * 10);
	if (!tab)
		return (1);
	int		tab_size = 0;
	int		maximum_size = 0;

	// Boucle principale
	int running = 1;
	SDL_Event event;

	while (running) {

		// Gestion des événements
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = 0;
					break;

				case SDL_WINDOWEVENT: {
					// Gérer le redimensionnement de la fenêtre
					if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
						window_width = event.window.data1;
						window_height = event.window.data2;
					}
					break;
				}

				case SDL_MOUSEWHEEL: {
					// Zoom et dézoom
					int mouse_x, mouse_y;
					SDL_GetMouseState(&mouse_x, &mouse_y);

					// Position de la souris dans la grille avant le zoom
					float grid_mouse_x = (mouse_x - offset_x) / cell_size;
					float grid_mouse_y = (mouse_y - offset_y) / cell_size;

					// Changer la taille des cellules en fonction de la molette
					if (event.wheel.y > 0) {
						cell_size *= 1.1f; // Zoomer
					} else if (event.wheel.y < 0) {
						cell_size *= 0.9f; // Dézoomer
					}

					// Limiter la taille minimale et maximale des cellules
					if (cell_size < 5) cell_size = 5;
					if (cell_size > 100) cell_size = 100;

					// Ajuster le décalage pour zoomer sur la position de la souris
					offset_x = mouse_x - grid_mouse_x * cell_size;
					offset_y = mouse_y - grid_mouse_y * cell_size;
					break;
				}

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						mouse_pan = 1; // Activer le pan
						SDL_GetMouseState(&last_mouse_x, &last_mouse_y);
					} else if (event.button.button == SDL_BUTTON_RIGHT) {
						// Récupérer les coordonnées de la cellule
						int mouse_x, mouse_y;
						SDL_GetMouseState(&mouse_x, &mouse_y);

						// Calculer les coordonnées de la cellule
						int cell_x = (mouse_x - offset_x) / cell_size;
						int cell_y = (mouse_y - offset_y) / cell_size;

						// printf("Clic droit sur la cellule : (%d, %d)\n", cell_x, cell_y);

						t_cell	*new_cell;
						new_cell = malloc(sizeof(t_cell));
						if (!new_cell)
							return (1);
						new_cell->state = 1;
						new_cell->x = cell_x;
						new_cell->y = cell_y;

						int	contains = 0;

						if (tab && tab_size > 0)
							contains = tab_contains_double(tab, new_cell, tab_size);
						if (contains == 0)
							tab_size++;

						printf("1\n");
						if (maximum_size / 10 <= tab_size / 10)
						{
							tab = realloc(tab, sizeof(t_cell *) * (tab_size / 10 * 10 + 10));
							if (!tab)
								return (1);
						}

						printf("2\n");
						if (contains == 0)
							tab[tab_size - 1] = new_cell;
						else
						{
							free(new_cell);
							new_cell = NULL;
						}
						printf("3\n");
					}
					break;

				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT) {
						mouse_pan = 0; // Désactiver le pan
					}
					break;

				case SDL_MOUSEMOTION:
					if (mouse_pan) {
						int mouse_x, mouse_y;
						SDL_GetMouseState(&mouse_x, &mouse_y);

						// Calcul du déplacement de la souris
						int dx = mouse_x - last_mouse_x;
						int dy = mouse_y - last_mouse_y;

						// Appliquer le décalage au pan
						offset_x += dx;
						offset_y += dy;

						// Mettre à jour la dernière position de la souris
						last_mouse_x = mouse_x;
						last_mouse_y = mouse_y;
					}
					break;

				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_SPACE) {
						printf("4\n");
						tab = get_newtab(tab, tab_size);
						printf("5\n");
						if (tab)
						{
							printf("6\n");
							tab_size = tab[0]->lenght;
							if (tab_size > maximum_size)
								maximum_size = tab_size;
							printf("7\n");
						}
						else
						{
							printf("8\n");
							tab = malloc(sizeof(t_cell *) * 10);
							tab_size = 0;
							printf("9\n");
						}
						printf("10\n");
					}
					break;
			}
		}

		// Effacer l'écran (remplir de noir)
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		// Dessiner la grille avec zoom et décalage
		draw_grid(renderer, window_width, window_height, cell_size, offset_x, offset_y);

		// Dessiner les cellules
		if (tab_size)
		{
			int	i = 0;
			while (i < tab_size)
				draw_cell(renderer, tab[i++], cell_size, offset_x, offset_y);
		}

		// Afficher les changements à l'écran
		SDL_RenderPresent(renderer);

		// Limiter la vitesse d'affichage (facultatif)
		SDL_Delay(8);
	}

	// Nettoyage
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
