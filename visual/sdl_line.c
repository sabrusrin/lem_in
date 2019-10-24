/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 01:07:24 by chermist          #+#    #+#             */
/*   Updated: 2019/10/23 18:40:46 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define POINTS_COUNT 3

static SDL_Point points[POINTS_COUNT] = {
    {300, 240},
    {340, 240},
    {320, 200}
};

int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer;
	SDL_DisplayMode	dispmode;
    SDL_Window *win;
    int i;
	int	w, h;

    SDL_Init(SDL_INIT_VIDEO);
/* 	win = SDL_CreateWindow("lem-in",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				dispmode.w, dispmode.h, SDL_WINDOW_FULLSCREEN);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED); */
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI, &win, &renderer);
	SDL_GL_GetDrawableSize(win, &w, &h);
	printf("W: %d   H: %d\n", w, h);
	//SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
//		SDL_RenderSetScale(renderer, 0.5, 0.5);
    SDL_SetRenderDrawColor(renderer, 10, 30, 41, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(renderer, i, i);
	SDL_RenderDrawLine(renderer, 50, 300, 450, 200);
	thickLineRGBA(renderer, 100, 50, 500, 550, 7, 102, 102, 102, 255);
	filledCircleRGBA(renderer, 1000, 1000, 100, 70, 70, 75, 255);
    aacircleRGBA (renderer, 1000, 1000, 100, 255, 255, 255, 255);
	SDL_RenderDrawLines(renderer, points, POINTS_COUNT);
	//SDL_RenderClear(renderer);
//	filledPieRGBA (renderer, 400, 100, 30, 10, 20, 200, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(renderer);
    while (1) {
        if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				printf("KK\n");
				break;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
				{
					printf("OO\n");
					break;
				}
		}
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return EXIT_SUCCESS;
}
//gcc sdl_line.c -o line `sdl2-config --cflags` `sdl2-config --libs` -lSDL2_gfx -lSDL2_ttf -lm