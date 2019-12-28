/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:23:04 by chermist          #+#    #+#             */
/*   Updated: 2019/10/26 17:33:21 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <SDL.h>
# include <SDL2_gfxPrimitives.h>
# include <SDL_ttf.h>
# include "lem_in.h"
# include <stdlib.h>

typedef struct		s_visu
{
	int				radius;
	int				d;
	int				wh[2];
	Uint32			clr[4];
	SDL_Event		event;
	SDL_Renderer	*rend;
	SDL_Window		*win;
	t_vec			*t_surf;
	t_vec			*t_tex;
	t_vec			*rect;
	TTF_Font		*font;
	SDL_Surface		*surface;
}					t_visu;

#endif
