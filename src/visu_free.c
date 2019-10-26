/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 03:27:17 by chermist          #+#    #+#             */
/*   Updated: 2019/10/26 04:39:23 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	visu_free(t_support *sup, t_visu *v)
{
	int		i[2];
	t_vec	*moves;
	t_move	*move;
	t_lines	*l;

	i[0] = -1;
	if (sup->moves)
		while (++i[0] < sup->moves->size &&
			(moves = *(t_vec**)ft_vat(sup->moves, i[0])))
		{
			i[1] = -1;
			while (++i[1] < moves->size)
			{
				move = *(t_move**)ft_vat(moves, i[1]);
				ft_memdel((void**)&move);
			}
			ft_vdel(&moves);
		}
	ft_vdel(&sup->moves);
	i[0] = -1;
	while (++i[0] < sup->lines->size &&
		(l = *(t_lines**)ft_vat(sup->lines, i[0])))
		ft_memdel((void**)&l);
	ft_vdel(&sup->lines);
}
