/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:22:28 by chermist          #+#    #+#             */
/*   Updated: 2019/10/24 03:06:24 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	print_lines(t_support *sup, t_visu *v)
{
	int			i;
	t_lines		*ab;

	i = -1;
	while (++i < sup->lines->size)
	{
		ab = *(t_lines**)ft_vat(sup->lines, i);
		thickLineRGBA(v->rend, ab->a->x, ab->a->y,
			ab->b->x, ab->b->y, 5, 102, 102, 102, 255);
	}
}

void	print_rooms(t_support *sup, t_visu *v)
{
	int		i;
	t_lem	*room;

	i = -1;
	while (++i < sup->farm->size)
	{
		room = *(t_lem**)ft_vat(sup->farm, i);
		if (room->status == 1)
			filledCircleRGBA(v->rend, room->x, room->y,
				v->radius, 0, 186, 186, 255);
		else if (room->status == 2)
			filledCircleRGBA(v->rend, room->x, room->y,
				v->radius, 205, 98, 87, 255);
		else
			filledCircleRGBA(v->rend, room->x, room->y,
				v->radius, 70, 70, 75, 255);
    	aacircleRGBA(v->rend, room->x, room->y,
			v->radius, 255, 255, 255, 255);
	}
}

int		visu_init(t_support *sup, t_visu *v)
{
	int i;
	float	wh[2];
	int	w, h;
	float	mp;
	t_lem	*room;

	wh[0] = sup->xy[1][0] - sup->xy[0][0];
	wh[1] = sup->xy[1][1] - sup->xy[0][1];
	if (wh[0] > wh[1])
		mp = (float)(1200 - 100 * 2) / ((wh[0] != 0) ? wh[0] : 1);
	else
		mp = (float)(1200 - 100 * 2) / ((wh[1] != 0) ? wh[1] : 1);
	i = -1;
	while (++i < sup->farm->size)
	{
		room = *(t_lem**)ft_vat(sup->farm, i);
		room->x = ((room->x - sup->xy[0][0]) * mp + 100) * 2;
		room->y = ((room->y - sup->xy[0][1]) * mp + 100) * 2;
	}
	wh[0] = wh[0] * mp + 100 * 2;
	wh[1] = wh[1] * mp + 100 * 2;
	v->radius = (1120 / ft_sqrt((sup->farm->size + 10) * 4) / 3) * 2;	

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(wh[0], wh[1], SDL_WINDOW_ALLOW_HIGHDPI,
		   	&v->win, &v->rend);
	SDL_SetRenderDrawColor(v->rend, 10, 30, 41, 0);
	SDL_RenderClear(v->rend);
	SDL_SetRenderDrawColor(v->rend, 255, 0, 0, 255);

	SDL_GL_GetDrawableSize(v->win, &w, &h);
	ft_printf("W: %d   H: %d\n", w, h);

	print_lines(sup, v);
	print_rooms(sup, v);

	//SDL_RenderDrawLine(v->rend, 50, 300, 450, 200);
	//SDL_RenderClear(renderer);
//	filledPieRGBA (renderer, 400, 100, 30, 10, 20, 200, 200, 200, SDL_ALPHA_OPAQUE);
	  SDL_RenderPresent(v->rend);
    while (1) {
        if (SDL_PollEvent(&v->event))
		{
			if (v->event.type == SDL_QUIT)
			{
				printf("KK\n");
				break;														
			}
			if (v->event.type == SDL_KEYDOWN &&
			v->event.key.keysym.sym == SDLK_ESCAPE)
			{
				printf("OO\n");
				break;
			}
		}
    }
    SDL_DestroyRenderer(v->rend);
    SDL_DestroyWindow(v->win);
    SDL_Quit();
    return EXIT_SUCCESS; 
}
