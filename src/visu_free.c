/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 03:27:17 by chermist          #+#    #+#             */
/*   Updated: 2019/10/26 15:04:07 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		visu_free(t_support *sup)
{
	int		i[2];
	t_vec	*moves;
	t_move	*move;
	t_lines	*l;

	i[0] = -1;
	if (sup->moves)
		while (++i[0] < (int)sup->moves->size &&
			(moves = *(t_vec**)ft_vat(sup->moves, i[0])))
		{
			i[1] = -1;
			while (++i[1] < (int)moves->size)
			{
				move = *(t_move**)ft_vat(moves, i[1]);
				ft_memdel((void**)&move);
			}
			ft_vdel(&moves);
		}
	ft_vdel(&sup->moves);
	i[0] = -1;
	while (++i[0] < (int)sup->lines->size &&
		(l = *(t_lines**)ft_vat(sup->lines, i[0])))
		ft_memdel((void**)&l);
	ft_vdel(&sup->lines);
}

SDL_Texture	*visu_text(t_visu *v, char *text, SDL_Rect *rect, int xy[])
{
	SDL_Color	color;
	SDL_Surface *surface;
	SDL_Texture *texture;
	int			wh[2];

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	surface = TTF_RenderText_Solid(v->font, text, color);
	texture = SDL_CreateTextureFromSurface(v->rend, surface);
	wh[0] = surface->w;
	wh[1] = surface->h;
	SDL_FreeSurface(surface);
	rect->x = xy[0];
	rect->y = xy[1];
	rect->w = wh[0];
	rect->h = wh[1];
	return (texture);
}

void		print_se(t_visu *v, SDL_Texture *texture, SDL_Rect rect, int xy[])
{
	SDL_SetRenderDrawColor(v->rend, 10, 30, 41, 0);
	SDL_RenderClear(v->rend);
	xy[0] = 10;
	xy[1] = 10;
	texture = visu_text(v, "Start ", &rect, xy);
	SDL_RenderCopy(v->rend, texture, NULL, &rect);
	xy[0] = v->wh[0] / 2;
	texture = visu_text(v, "End ", &rect, xy);
	SDL_RenderCopy(v->rend, texture, NULL, &rect);
}
