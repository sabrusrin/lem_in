/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:20:32 by chermist          #+#    #+#             */
/*   Updated: 2019/10/26 04:35:50 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		handle_event(t_visu *v)
{
	int	i;

	i = 1;
	if (v->event.type == SDL_QUIT || (v->event.type == SDL_KEYDOWN &&
		v->event.key.keysym.sym == SDLK_ESCAPE))
		return (1);
	else if (v->event.type == SDL_KEYDOWN &&
		v->event.key.keysym.sym == SDLK_SPACE)
		while (i)
			if (SDL_PollEvent(&v->event) && v->event.type == SDL_KEYDOWN &&
				v->event.key.keysym.sym == SDLK_SPACE)
				i = 0;
	return (0);
}

void	put_default(t_support *sup, t_visu *v)
{
	SDL_SetRenderDrawColor(v->rend, 10, 30, 41, 0);
	SDL_RenderClear(v->rend);
	print_lines(sup, v);
	print_rooms(sup, v);
}

void	do_move(t_move *move, t_visu *v, int i[])
{
	move->a[0] -= move->delta[0];
	move->a[1] -= move->delta[1];
	filledCircleRGBA(v->rend, move->a[0], move->a[1],
	v->radius / 3, 0, 186, 186, 255);
	aacircleRGBA(v->rend, move->a[0], move->a[1],
	v->radius / 3, 255, 255, 255, 255);
}

int		move_ants(t_support *sup, t_visu *v)
{
	int		i[3];
	t_move	*move;
	t_vec	*moves;

	i[0] = -1;
	while (++i[0] < sup->moves->size)
	{
		moves = *(t_vec**)ft_vat(sup->moves, i[0]);
		usleep(400000);
		i[1] = -1;
		while (++i[1] < 15 && (i[2] = -1))
		{
			if (SDL_PollEvent(&v->event) && handle_event(v))
				return (0);
			put_default(sup, v);
			while (++i[2] < moves->size)
			{
				move = *(t_move**)ft_vat(moves, i[2]);
				do_move(move, v, i);
			}
			SDL_RenderPresent(v->rend);
		}
	}
	return (1);
}

int		visu_move(t_support *sup, t_visu *v)
{
	int		i;

	i = 1;
	while (1)
		if (SDL_PollEvent(&v->event))
			if (v->event.type == SDL_KEYDOWN &&
				v->event.key.keysym.sym == SDLK_SPACE)
			{
				i = move_ants(sup, v);
				break ;
			}
	put_default(sup, v);
	SDL_RenderPresent(v->rend);
	while (i)
		if (SDL_PollEvent(&v->event))
			if (v->event.type == SDL_QUIT || (v->event.type == SDL_KEYDOWN &&
				v->event.key.keysym.sym == SDLK_ESCAPE))
				break ;
	SDL_DestroyRenderer(v->rend);
	SDL_DestroyWindow(v->win);
	TTF_Quit();
	SDL_Quit();
	visu_free(sup, v);
	return (EXIT_SUCCESS);
}
