/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 22:31:11 by chermist          #+#    #+#             */
/*   Updated: 2019/10/24 22:31:41 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <stdlib.h>

int main()
{
    SDL_Window *o;
    SDL_Renderer *r;
    SDL_Event e;
    SDL_Rect q;
    int i =1;

    SDL_Init(SDL_INIT_VIDEO);

    o = SDL_CreateWindow("Game test",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            1024,
                            800,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    r = SDL_CreateRenderer(o, -1,SDL_RENDERER_ACCELERATED);

    while(i)
    {
        while(SDL_PollEvent(&e) !=0)
        {
            if(e.type == SDL_QUIT)
                i=0;
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_q:
                    i=0;
                break;
                case SDLK_UP:
                    q.y -=10;
                break;
                case SDLK_DOWN:
                    q.y +=10;
                break;
                case SDLK_RIGHT:
                    q.x +=10;
                break;
                case SDLK_LEFT:
                    q.x -=10;
                break;
                }
            }
        }
        SDL_SetRenderDrawColor(r,0,0,255,255);
        SDL_RenderClear(r);
        // Creating the rectangle
        q.x=475;
        q.y=700;
        q.h=50;
        q.w=50;

        SDL_SetRenderDrawColor(r,0,0,0,255);

        SDL_RenderFillRect(r,&q);

        SDL_RenderPresent(r);
    }

    SDL_DestroyWindow(o);
    SDL_DestroyRenderer(r);
    SDL_Quit();

    return 0;
}