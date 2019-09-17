/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:29 by chermist          #+#    #+#             */
/*   Updated: 2019/09/17 23:17:36 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	bfs(int	i, t_support *sup)
{
	t_vec	*queue;

}

void	path_find(t_support *sup)
{
	t_lem	*room;
	t_vec	*shortest;
	int		i;

	i = -1;
	while (++i < sup->farm->size)
	{
		room = *(t_lem**)ft_vat(sup->farm, i);
		if (room->room_status == 1)
			break;
	}
	bfs(i, sup);
}
