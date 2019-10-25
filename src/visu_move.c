/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:20:32 by chermist          #+#    #+#             */
/*   Updated: 2019/10/25 22:57:18 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	move_ants(t_support *sup, t_visu *v)
{
//	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
	int		i;
	int		j;
	int		k;
	t_move	*move;
	t_vec	*moves;

	i = -1;
	ft_printf("lines: %d\n", sup->moves->size);
	while (++i < sup->moves->size)
	{
		write(1, "move\n", 5);
		moves = *(t_vec**)ft_vat(sup->moves, i);
		j = -1;
		move = *(t_move**)ft_vat(moves, 0);
		ft_printf("move: %d %d %d\n", moves->size, move->a[0], move->a[1]);
		while (++j < 10)
		{
			SDL_RenderClear(v->rend);
			SDL_SetRenderDrawColor(v->rend, 10, 30, 41, 0);
			print_lines(sup, v);
			print_rooms(sup, v);
			k = -1;
			while (++k < moves->size)
			{
				move = *(t_move**)ft_vat(moves, k);
				move->a[0] += move->delta[0];
				move->a[1] += move->delta[1];
				filledCircleRGBA(v->rend, move->a[0], move->a[1],
				v->radius / 3, 70, 70, 75, 255);
				usleep(50000);
			}
			SDL_RenderPresent(v->rend);
		}
	}
}

int		visu_move(t_support *sup, t_visu *v)
{
	while (1)
		if (SDL_PollEvent(&v->event))
			if (v->event.type == SDL_KEYDOWN &&
				v->event.key.keysym.sym == SDLK_SPACE)
				move_ants(sup, v);
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
