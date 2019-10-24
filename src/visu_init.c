/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:22:28 by chermist          #+#    #+#             */
/*   Updated: 2019/10/25 00:16:41 by chermist         ###   ########.fr       */
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

SDL_Texture	*create_text(t_lem *room, t_visu *v, char *text, SDL_Rect *rect)
{
	SDL_Color 	color = {255, 255, 255};
	SDL_Surface *surface;
	SDL_Texture *texture;
	int			wh[2];

	surface = TTF_RenderText_Solid(v->font, text, color);
	texture = SDL_CreateTextureFromSurface(v->rend, surface);
	wh[0] = surface->w;
	wh[1] = surface->h;
	SDL_FreeSurface(surface);
	rect->x = room->x - v->radius /
		(ft_strlen(text) > 1 ? ft_strlen(text) : 5);
	rect->y = room->y - v->radius / 3;
	rect->w = wh[0];
	rect->h = wh[1];
	return (texture);
}

void	print_rooms(t_support *sup, t_visu *v)
{
	int			i;
	SDL_Rect	rect;
	t_lem		*room;
	SDL_Texture	*texture;

	i = -1;
	v->font = TTF_OpenFont("futura medium bt.ttf", v->radius / 2);
	while (++i < sup->farm->size && (room = *(t_lem**)ft_vat(sup->farm, i)))
	{
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
		texture = create_text(room, v, room->name, &rect);
		SDL_RenderCopy(v->rend, texture, NULL, &rect);
		SDL_DestroyTexture(texture);
	}
	TTF_CloseFont(v->font);
}

void	set_defaults(t_support *sup, t_visu *v, double wh[])
{
	int		i;
	double	mp;
	t_lem	*room;

	wh[0] = sup->xy[1][0] - sup->xy[0][0];
	wh[1] = sup->xy[1][1] - sup->xy[0][1];
	if (wh[0] > wh[1])
		mp = (double)(1200 - 100 * 2) / ((wh[0] != 0) ? wh[0] : 1);
	else
		mp = (double)(1200 - 100 * 2) / ((wh[1] != 0) ? wh[1] : 1);
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
}

int		visu_init(t_support *sup, t_visu *v)
{
	double	wh[2];
	double	mp;
	int		hw[2];

	set_defaults(sup, v, wh);
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_CreateWindowAndRenderer(wh[0], wh[1], SDL_WINDOW_ALLOW_HIGHDPI,
								&v->win, &v->rend);
	SDL_Renderer* rend = SDL_CreateRenderer(v->win, -1, SDL_RENDERER_ACCELERATED);//
	SDL_SetRenderDrawColor(v->rend, 255, 0, 0, 255);//
	SDL_RenderDrawLine(rend, 100, 100, 500, 500);
	SDL_SetRenderDrawColor(v->rend, 10, 30, 41, 0);
	SDL_RenderClear(v->rend);
//	SDL_SetRenderDrawColor(v->rend, 255, 0, 0, 255);
	SDL_GL_GetDrawableSize(v->win, &hw[0], &hw[1]);
	ft_printf("W: %d   H: %d\n", hw[0], hw[1]);
	print_lines(sup, v);
	print_rooms(sup, v);
	SDL_RenderPresent(v->rend);
	SDL_RenderPresent(rend);
	return (EXIT_SUCCESS);
}
