/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:23:04 by chermist          #+#    #+#             */
/*   Updated: 2019/10/25 22:57:22 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <SDL.h>
# include <SDL2_gfxPrimitives.h>
# include <SDL_ttf.h>
# include "lem_in.h"
# include <stdlib.h>

#define WINDOW_WIDTH 600

typedef struct		s_ants
{
	int				x;
	int				y;
	SDL_Texture		*tex_ant;
	SDL_Rect		dest;
}					t_ants;

typedef struct		s_visu
{
	int				scale[2];
	int				off[2];
	int				*lines[2];
	int				radius;
	int				d;
	Uint32			clr[4];
	SDL_Event		event;
	SDL_Renderer	*rend;
	SDL_Window		*win;
//	SDL_Texture		*layer[4];
	t_vec			*t_surf;
	t_vec			*t_tex;
	t_vec			*rect;
	TTF_Font		*font;
	SDL_Surface 	*surface;
}					t_visu;

#endif
