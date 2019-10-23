/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:22:28 by chermist          #+#    #+#             */
/*   Updated: 2019/10/23 15:38:23 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	save_lines(t_support *sup, t_visu *v)
{

}

int		visu_init(t_support *sup, t_visu *v)
{
	int i;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(1280, 720, SDL_WINDOW_ALLOW_HIGHDPI,
		   	&v->win, &v->rend);
//		SDL_RenderSetScale(renderer, 0.5, 0.5);
	SDL_SetRenderDrawColor(v->rend, 10, 30, 41, 0);
	SDL_RenderClear(v->rend);
	SDL_SetRenderDrawColor(v->rend, 255, 0, 0, 255);
//	save_lines(sup, v);
 	 for (i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(v->rend, i, i);
	SDL_RenderDrawLine(v->rend, 50, 300, 450, 200);
	thickLineRGBA(v->rend, 100, 50, 500, 550, 5, 102, 102, 102, 255);
	filledCircleRGBA(v->rend, 40, 40, 30, 70, 70, 75, 255);
    aacircleRGBA(v->rend, 40, 40, 30, 255, 255, 255, 255);
	//SDL_RenderClear(renderer);
//	filledPieRGBA (renderer, 400, 100, 30, 10, 20, 200, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(v->rend);
    while (1) {
        if (SDL_PollEvent(&v->event))
		{
			if ((v->event.type == SDL_QUIT) ||
				(v->event.key.keysym.sym == SDLK_ESCAPE))
				break;
		}
    }
    SDL_DestroyRenderer(v->rend);
    SDL_DestroyWindow(v->win);
    SDL_Quit();
    return EXIT_SUCCESS; 
}
