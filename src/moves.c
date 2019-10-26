/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:24:57 by chermist          #+#    #+#             */
/*   Updated: 2019/10/26 15:00:51 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	save_move(t_support *sup, t_vec *path, t_lem *room, int i[])
{
	t_vec		*moves;
	t_move		*move;
	t_lem		*prev;
	t_lem		*start;
	t_lem		*end;

	moves = *(t_vec**)ft_vback(sup->moves);
	move = malloc(sizeof(t_move));
	prev = *(t_lem**)ft_vat(path, i[2] - 1);
	move->a[0] = prev->x;
	move->a[1] = prev->y;
	move->b[0] = room->x;
	move->b[1] = room->y;
	move->delta[0] = (float)(move->a[0] - move->b[0]) / 30;
	move->delta[1] = (float)(move->a[1] - move->b[1]) / 30;
	start = *(t_lem**)ft_vat(path, 0);
	move->se[0] = start->ants;
	end = *(t_lem**)ft_vback(path);
	move->se[1] = end->ants;
	ft_vpush_back(moves, &move, sizeof(t_move*));
}

void	move_to_end(t_support *sup, t_vec *path)
{
	int		i;
	int		j[4];
	t_lem	*end;

	i = 0;
	j[2] = 1;
	end = *(t_lem**)ft_vback(path);
	while (++i <= sup->ants)
		ft_printf("L%d-%s ", i, end->name);
	ft_putchar('\n');
	if (sup->opt.visu)
	{
		sup->moves = ft_vnew(30, sizeof(t_vec*));
		save_move(sup, path, end, j);
	}
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
	if (!(i[0] = 0) && sup->opt.visu)
		sup->moves = ft_vnew(30, sizeof(t_vec*));
	while (i[0] < sup->ants && (i[1] = -1))
	{
		if (sup->opt.visu && (move = ft_vnew(10, sizeof(t_move*))))
			ft_vpush_back(sup->moves, &move, sizeof(t_vec*));
		while (++i[1] < (int)p->size && (i[2] = -1) &&
			(path = *(t_vec**)ft_vat(p, i[1])))
		{
			i[3] = 0;
			while (++i[2] < (int)path->size)
			{
				chk_room(p, &room, &count, i);
				moves(sup, path, room, i);
			}
		}
		write(1, "\n", 1);
	}
}
