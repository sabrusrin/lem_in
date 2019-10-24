/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:20:32 by chermist          #+#    #+#             */
/*   Updated: 2019/10/25 00:16:31 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	move_ants(t_support *sup, t_visu *v)
{
//	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
}

int		visu_move(t_support *sup, t_visu *v)
{
//	move_ants(sup, v);
	while (1)
	{
		if (SDL_PollEvent(&v->event))
		{
			if (v->event.type == SDL_QUIT)
				break ;
			if (v->event.type == SDL_KEYDOWN &&
				v->event.key.keysym.sym == SDLK_ESCAPE)
				break ;
		}
	}
	SDL_DestroyRenderer(v->rend);
	SDL_DestroyWindow(v->win);
	TTF_Quit();
	SDL_Quit();
	return (EXIT_SUCCESS);
}
