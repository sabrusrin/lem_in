/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 01:07:24 by chermist          #+#    #+#             */
/*   Updated: 2019/10/22 12:44:46 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#define WINDOW_WIDTH 600

int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int i;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 10, 30, 41, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(renderer, i, i);
	SDL_RenderDrawLine(renderer, 50, 300, 450, 200);
	thickLineRGBA(renderer, 100, 50, 500, 550, 5, 102, 102, 102, 255);
	filledCircleRGBA(renderer, 40, 40, 30, 70, 70, 75, 255);
    aacircleRGBA (renderer, 40, 40, 30, 255, 255, 255, 255);
//	filledPieRGBA (renderer, 400, 100, 30, 10, 20, 200, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(renderer);
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}