/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:23:04 by chermist          #+#    #+#             */
/*   Updated: 2019/10/23 15:24:00 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <SDL.h>
# include <SDL2_gfxPrimitives.h>
# include "lem_in.h"
# include <stdlib.h>

#define WINDOW_WIDTH 600

typedef struct		s_visu
{
	int				*lines[2];
	Uint32			clr[4];
	SDL_Event		event;
	SDL_Renderer	*rend;
	SDL_Window		*win;
	SDL_Texture		*layer[4];
}					t_visu;

#endif
