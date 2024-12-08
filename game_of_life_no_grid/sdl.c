/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:48:31 by agruet            #+#    #+#             */
/*   Updated: 2024/12/08 11:51:50 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

#define INITIAL_CELL_SIZE 20
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void	draw_grid(SDL_Renderer *renderer, int window_width, int window_height, float cell_size, float offset_x, float offset_y)
{
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);

	for (float y = fmodf(offset_y, cell_size); y <= window_height; y += cell_size) {
		SDL_RenderDrawLine(renderer, 0, y, window_width, y);
	}

	for (float x = fmodf(offset_x, cell_size); x <= window_width; x += cell_size) {
		SDL_RenderDrawLine(renderer, x, 0, x, window_height);
	}
}

void	draw_cell(SDL_Renderer *renderer, t_cell *cell, float cell_size, float offset_x, float offset_y)
{
	if (cell->state == 1) {
		SDL_Rect rect;
		rect.x = (cell->x * cell_size) + offset_x;
		rect.y = (cell->y * cell_size) + offset_y;
		rect.w = cell_size + 1;
		rect.h = cell_size + 1;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &rect);
	}
}

int	main(int ac, char **av)
{
	// 0: Game Of Life
	// 1: High Life
	int game = 0;

	if (ac > 1)
	{
		if (strcmp(av[1], "hl") == 0)
			game = 1;
	}

	int	sdl = SDL_Init(SDL_INIT_VIDEO);
	if (sdl) {
		printf("Erreur SDL_Init: %s\n", SDL_GetError());
		return (1);
	}

	int window_width = WINDOW_HEIGHT, window_height = WINDOW_HEIGHT;

	SDL_Window *window = SDL_CreateWindow("Game Of Life",
									SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
									window_width, window_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
	if (!window) {
		printf("Error SDL_CreateWindow: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("Error SDL_CreateRenderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}

	// Variables for zoom and pan
	float cell_size = INITIAL_CELL_SIZE;
	float offset_x = 0, offset_y = 0; // Pan offset
	int mouse_pan = 0; // Pan active
	int last_mouse_x = 0, last_mouse_y = 0; // Last mouse pos

	// Create tab
	int maximum_size = 10;
	t_cell	**tab;
	tab = malloc(sizeof(t_cell *) * maximum_size);
	if (!tab)
		return (1);
	int tab_size = 0;

	// Enable grid rendering
	int enable_grid = 1;

	// Main loop
	int running = 1;
	SDL_Event event;

	while (running) {
		// Events management
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = 0;
					break;

				case SDL_WINDOWEVENT: {
					// Handle window resize
					if (event.window.event == SDL_WINDOWEVENT_RESIZED)
						window_width = event.window.data1, window_height = event.window.data2;
					break;
				}

				case SDL_MOUSEWHEEL: {
					// Zoom management
					int mouse_x, mouse_y;
					SDL_GetMouseState(&mouse_x, &mouse_y);

					// Mouse pos before zoom
					float grid_mouse_x = (mouse_x - offset_x) / cell_size;
					float grid_mouse_y = (mouse_y - offset_y) / cell_size;

					// Change cells size with mouse wheel
					if (event.wheel.y > 0)
						cell_size *= 1.1f; // Zoom In
					else if (event.wheel.y < 0)
						cell_size *= 0.9f; // Zoom Out

					// Limit min and max cells size
					if (cell_size < 2) cell_size = 2; // Max zoom out
					if (cell_size > 100) cell_size = 100; // Max zoom in

					// Adjust offset to zoom in on mouse position
					offset_x = mouse_x - grid_mouse_x * cell_size;
					offset_y = mouse_y - grid_mouse_y * cell_size;
					break;
				}

				case SDL_MOUSEBUTTONUP: {
					if (event.button.button == SDL_BUTTON_LEFT)
						mouse_pan = 0; // Disable pan
					break;
				}

				case SDL_MOUSEMOTION: {
					if (mouse_pan) {
						int mouse_x, mouse_y;
						SDL_GetMouseState(&mouse_x, &mouse_y);

						// Calculating mouse movement
						int dx = mouse_x - last_mouse_x;
						int dy = mouse_y - last_mouse_y;

						// Apply offset to pan
						offset_x += dx;
						offset_y += dy;

						// Update last mouse position
						last_mouse_x = mouse_x;
						last_mouse_y = mouse_y;
					}
					break;
				}

				case SDL_MOUSEBUTTONDOWN: {
					if (event.button.button == SDL_BUTTON_LEFT) {
						mouse_pan = 1; // Turn pan on
						SDL_GetMouseState(&last_mouse_x, &last_mouse_y);
					} else if (event.button.button == SDL_BUTTON_RIGHT) {
						// Retrieve cell coordinates
						int mouse_x, mouse_y;
						SDL_GetMouseState(&mouse_x, &mouse_y);

						// Calculate cell coordinates
						int cell_x = (mouse_x - offset_x) / cell_size;
						int cell_y = (mouse_y - offset_y) / cell_size;

						// Create a new t_cell at coords
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

						if (tab_size > maximum_size) {
							maximum_size += 10;
							tab = realloc(tab, sizeof(t_cell *) * maximum_size);
							if (!tab)
								return (0);
						}

						if (contains == 0)
							tab[tab_size - 1] = new_cell;
						else
							free(new_cell);
					}
					break;
				}

				case SDL_KEYDOWN: {
					if (event.key.keysym.sym == SDLK_SPACE) {
						tab = get_newtab(tab, tab_size, game);
						if (tab)
						{
							tab_size = tab[0]->lenght;
							maximum_size = tab_size / 10 * 10 + 10;
						}
						else
						{
							tab = malloc(sizeof(t_cell *) * 10);
							tab_size = 0;
							maximum_size = 10;
						}
					}
					else if (event.key.keysym.sym == SDLK_g)
						enable_grid = -enable_grid;
					break;
				}
			}
		}

		// Black out
		SDL_SetRenderDrawColor(renderer, 15, 15, 15, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		// Draw grid
		if (enable_grid == 1)
			draw_grid(renderer, window_width, window_height, cell_size, offset_x, offset_y);

		// Draw cells
		if (tab_size) {
			int	i = 0;
			while (i < tab_size)
				draw_cell(renderer, tab[i++], cell_size, offset_x, offset_y);
		}

		// Show changes
		SDL_RenderPresent(renderer);

		// Limit FPS
		SDL_Delay(16);
	}

	// Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
