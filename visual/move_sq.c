/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 19:04:14 by chermist          #+#    #+#             */
/*   Updated: 2019/10/24 19:04:20 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include <assert.h>

/* linear interpolation between {start.x; start.y} and {end.x; end.y} */
static void rect_lerp(SDL_Rect *out, const SDL_Rect *start, const SDL_Rect *end, float f) {
    float t = 1.0f - f;
    out->x = (float)start->x * t + (float)end->x * f;
    out->y = (float)start->y * t + (float)end->y * f;
}

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    SDL_Window *window = SDL_CreateWindow("example",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            SDL_WINDOW_SHOWN);
    assert(window);
    SDL_Renderer *renderer =  SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    assert(renderer);

    int quit = 0;
    int animate = 0;
    Uint32 animation_start_time;

    /* whole animation will play in e.g. one seconds */
    const Uint32 animation_time_total = 1000;

    SDL_Rect rect0 = {
        .x = 0, .y = 0, .w = 128, .h = 128
    };
    SDL_Rect rect1 = {
        .x = 256, .y = 256, .w = 128, .h = 128
    };

    while(!quit) {
        /* time of current frame */
        Uint32 tcurrent = SDL_GetTicks();

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_KEYUP) {
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                    break;
                } else if(event.key.keysym.sym == SDLK_SPACE) {
                    animate = 1;
                    animation_start_time = tcurrent;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect r0 = rect0, r1 = rect1;
        /* if not within animation - leave coordinates as they are */
        if(animate) {
            if(tcurrent > animation_start_time + animation_time_total) {
                /* animation ends by now */
                /* swap rect0 and rect1 and stop animation */
                SDL_Rect t = rect0;
                rect0 = rect1;
                rect1 = t;
                animate = 0;

                /* need to update r0 and r1 too */
                r0 = rect0;
                r1 = rect1;
            } else {
                /* animation is incomplete - interpolate coordinates */
                /* calculate current animation percentage - in range [0; 1] */
                float factor = ((float)(tcurrent - animation_start_time)) / animation_time_total;
                rect_lerp(&r0, &rect0, &rect1, factor);
                rect_lerp(&r1, &rect1, &rect0, factor);
            }
        }

        /* r0 and r1 now have correct coordinates, draw */
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &r0);

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderDrawRect(renderer, &r1);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
