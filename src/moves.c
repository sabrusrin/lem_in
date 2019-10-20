/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:24:57 by chermist          #+#    #+#             */
/*   Updated: 2019/10/20 23:45:23 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_weight(t_vec *paths, t_vec *path, int j, int ants)
{
	t_vec *p;
	int	flow;
	int	pflow;
	int	minf;
	int	i;

	minf = 0;
	i = -1;
	flow = 0;
	while (++i <= j)
	{
		p = *(t_vec**)ft_vat(paths, i);
		flow += p->size - 1;
		i++;
//		pflow = flow / i + (ants - i) / i;
		pflow = ((flow - i) + (ants - i)) / i;
		i--;
		if (!minf || (minf > pflow))
			minf = pflow;
		if (pflow > minf && p == path)
		{
			return (0);
		}
	}
	return (1);
}

void	moves(t_lem *room, int i[])
{
	static int	ants = 0;

	if (room->status != 1)
	{
		if (i[3])
		{
			ft_printf("L%d-%s ", i[3], room->name);
			ants = room->ants;
			room->ants = i[3];
			i[3] = ants;
			if (room->status == 2)
				i[0]++;
		}
		else if (room->ants && room->status != 2)
		{
			i[3] = room->ants;
			room->ants = 0;
		}
	}
}

void	print_moves(t_vec *p, t_support *sup)
{
	int		i[4];
	int		count;
	t_lem	*room;
	t_vec	*path;

	count = 0;
	i[0] = 0;
	while (i[0] < sup->ants && (i[1] = -1))
	{
		while (++i[1] < p->size && (i[2] = -1) &&
			(path = *(t_vec**)ft_vat(p, i[1])))
		{
			i[3] = 0;
			while (++i[2] < path->size)
			{
				room = *(t_lem**)ft_vat(path, i[2]);
				if (room->status == 1 && room->ants &&
					check_weight(p, path, i[1], room->ants))
				{
					count++;
					room->ants--;
					i[3] = count;
					continue;
				}
				moves(room, i);
			}
		}
		write(1, "\n", 1);
	}
}
