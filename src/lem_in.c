/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:34 by chermist          #+#    #+#             */
/*   Updated: 2019/10/11 00:43:52 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	use_shortest(t_support *sup, t_vec *paths)
{
	int	i;
	t_vec *path;
	t_lem *room;
	
	i = 0;
	path = *(t_vec**)ft_vat(paths, 0);
	while (++i < path->size)
	{
		room = *(t_lem**)ft_vat(path, i);
		ft_printf("L1-%s\n", room->name);
	}

}

void	deal_conflict(t_support *sup, t_vec *paths)
{
	if (sup->ants == 1 || paths->size == 1)
		use_shortest(sup, paths);

}
