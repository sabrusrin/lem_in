/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:23:04 by chermist          #+#    #+#             */
/*   Updated: 2019/10/22 15:38:14 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <SDL.h>
# include <SDL2_gfxPrimitives.h>
# include "lem_in.h"

typedef struct		s_visu
{
	int				*lines[2];
	Uint32			clr[4];
	SDL_Event		event;
	SDL_Renderer	*renderer;
	SDL_Window		*window;
	SDL_Texture		*layer[4];
}					t_visu;

#endif