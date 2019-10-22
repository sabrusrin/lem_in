/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:22:28 by chermist          #+#    #+#             */
/*   Updated: 2019/10/23 01:27:30 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	save_lines(t_support *sup, t_visu *v)
{

}

void	visu_init(t_support *sup, t_visu *v)
{
	int i;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &v->window, &v->renderer);
//		SDL_RenderSetScale(renderer, 0.5, 0.5);
	SDL_SetRenderDrawColor(v->rend, 10, 30, 41, 0);
	SDL_RenderClear(v->rend);
	SDL_SetRenderDrawColor(v->rend, 255, 0, 0, 255);
	save_lines(sup, v);
 	 for (i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(renderer, i, i);
	SDL_RenderDrawLine(renderer, 50, 300, 450, 200);
	thickLineRGBA(renderer, 100, 50, 500, 550, 5, 102, 102, 102, 255);
	filledCircleRGBA(renderer, 40, 40, 30, 70, 70, 75, 255);
    aacircleRGBA (renderer, 40, 40, 30, 255, 255, 255, 255);
	//SDL_RenderClear(renderer);
//	filledPieRGBA (renderer, 400, 100, 30, 10, 20, 200, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(renderer);
    while (1) {
        if (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_QUIT) || (event.key.keysym.sym == SDLK_ESCAPE))
				break;
		}
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS; 
}
