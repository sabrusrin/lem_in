/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:29 by chermist          #+#    #+#             */
/*   Updated: 2019/10/26 03:05:24 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clean_up(t_vec *paths, t_queue *q)
{
	t_vec	*tmp;
	int		i;

	i = -1;
	if (q)
	{
		while (++i < q->capacity)
		{
			tmp = *(t_vec**)ft_qat(q, i);
			if (tmp)
				ft_vdel(&tmp);
		}
		ft_qdel(&q);
	}
	i = -1;
	if (paths)
		ft_vdel(&paths);
}

int		check_path(t_vec *path, t_lem *room)
{
	int i;

	i = -1;
	while (++i < path->size)
		if (room == *(t_lem**)ft_vat(path, i))
			return (0);
	return (1);
}

void	enqueue(t_lem *room, t_lem *start, t_vec *path, t_queue *q)
{
	t_vec *newpath;

	if (room->mark == 0 || room->mark > start->mark + 1)
		room->mark = start->mark + 1;
	newpath = ft_vdup(path);
	ft_vpush_back(newpath, &room, sizeof(t_lem*));
	ft_qpush(q, &newpath);
}

void	bfs(t_lem *start, t_vec *paths, t_queue *q)
{
	t_vec	*path;
	t_vec	*newpath;
	t_lem	*room;
	int		i;

	path = ft_vnew(5, sizeof(t_lem*));
	ft_vpush_back(path, &start, sizeof(t_lem*));
	ft_qpush(q, &path);
	while (!ft_qempty(q) && (path = *(t_vec**)ft_qpop(q)))
	{
		if ((start = *(t_lem**)ft_vback(path)) && start->status == 2)
		{
			ft_vpush_back(paths, &path, sizeof(t_vec*));
			if (paths->size > 500)
				break ;
			continue;
		}
		i = -1;
		while (++i < start->tubes->size &&
			(room = *(t_lem**)ft_vat(start->tubes, i)))
			if ((room->mark == 0 || room->mark >= start->mark
					|| start->tubes->size == 1 || room->status == 2)
					&& check_path(path, room))
				enqueue(room, start, path, q);
	}
}

void	path_find(t_support *sup)
{
	t_lem	*room;
	t_vec	*paths;
	t_vec	*tmp;
	t_queue	*q;
	int		i;

	i = -1;
	while (++i < sup->farm->size && (room = *(t_lem**)ft_vat(sup->farm, i)))
		if (room->status == 1 && (q = ft_qnew(1000000, sizeof(t_vec*))))
		{
			paths = ft_vnew(sup->farm->size, sizeof(t_vec*));
			bfs(room, paths, q);
			break ;
		}
	if (paths->size)
	{
		if (sup->opt.nomap == 0)
			print_in(sup);
		room->ants = sup->ants;
		lem_in(sup, paths);
	}
	else
		ft_printf("Error");
	clean_up(paths, q);
}
