/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:24:57 by chermist          #+#    #+#             */
/*   Updated: 2019/10/26 03:37:29 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_weight(t_vec *paths, t_vec *path, int j, int ants)
{
	t_vec	*p;
	int		flow;
	int		pflow;
	int		minf;
	int		i;

	minf = 0;
	i = -1;
	flow = 0;
	while (++i <= j)
	{
		p = *(t_vec**)ft_vat(paths, i);
		flow += p->size - 1;
		i++;
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

void	save_move(t_support *sup, t_vec *path, t_lem *room, int i[])
{
	t_vec		*moves;
	t_move		*move;
	t_lem		*prev;

	moves = *(t_vec**)ft_vback(sup->moves);
	move = malloc(sizeof(t_move));
	prev = *(t_lem**)ft_vat(path, i[2] - 1);
	move->a[0] = prev->x;
	move->a[1] = prev->y;
	move->b[0] = room->x;
	move->b[1] = room->y;
	move->delta[0] = (move->a[0] - move->b[0]) / 15;
	move->delta[1] = (move->a[1] - move->b[1]) / 15;
	ft_vpush_back(moves, &move, sizeof(t_move*));
}

void	moves(t_support *sup, t_vec *path, t_lem *room, int i[])
{
	static int	ants = 0;

	if (room->status != 1)
	{
		if (i[3])
		{
			if (sup->opt.visu)
				save_move(sup, path, room, i);
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

void	chk_room(t_vec *p, t_lem **room, int *count, int i[])
{
	t_vec	*path;

	path = *(t_vec**)ft_vat(p, i[1]);
	*room = *(t_lem**)ft_vat(path, i[2]);
	if ((*room)->status == 1 && (*room)->ants &&
		check_weight(p, path, i[1], (*room)->ants))
	{
		*count += 1;
		(*room)->ants--;
		i[3] = *count;
	}
}

void	print_moves(t_vec *p, t_support *sup)
{
	int		i[4];
	int		count;
	t_lem	*room;
	t_vec	*path;
	t_vec	*move;

	count = 0;
	i[0] = 0;
	while (i[0] < sup->ants && (i[1] = -1))
	{
		if (sup->opt.visu && (move = ft_vnew(10, sizeof(t_move*))))
			ft_vpush_back(sup->moves, &move, sizeof(t_vec*));
		while (++i[1] < p->size && (i[2] = -1) &&
			(path = *(t_vec**)ft_vat(p, i[1])))
		{
			i[3] = 0;
			while (++i[2] < path->size)
			{
				chk_room(p, &room, &count, i);
				moves(sup, path, room, i);
			}
		}
		write(1, "\n", 1);
	}
}
