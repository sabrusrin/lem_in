/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:29 by chermist          #+#    #+#             */
/*   Updated: 2019/09/20 20:06:13 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "stdio.h"

void	print_path(t_vec *path)
{
	int	i;
	t_lem *tmp;

	i = -1;
	while (++i < path->size)
	{
		tmp = *(t_lem**)ft_vat(path, i);
		printf("%s>>", tmp->name);
	}
	printf("\n");
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
	while (!ft_qempty(q))
	{
		path = *(t_vec**)ft_qpop(q);
		start = *(t_lem**)ft_vback(path);
//		printf("\n[%s]->", start->name);
//		if (start->link == start->tubes->size)
			start->mark = BLACK;
//		start->link++;
		if (start->room_status == 2)
		{
			ft_vpush_back(paths, &path, sizeof(t_vec*));
			print_path(path);
		}
		i = -1;
		while (++i < start->tubes->size)
		{
			room = *(t_lem**)ft_vat(start->tubes, i);
			if (room->mark != BLACK || room->room_status == 2)
			{
//			printf("|%s|\n", room->name);
				newpath = ft_vdup(path);
				ft_vpush_back(newpath, &room, sizeof(t_lem*));		
				ft_qpush(q, &newpath);// problem is here, for some reason newpath being pushed incorrectly
				room->mark = GRAY;
			}
		}
	}
}

void	path_find(t_support *sup)
{
	t_lem	*room;
	t_vec	*paths;
	t_queue	*q;
	int		i;

	i = -1;
	while (++i < sup->farm->size)
	{
		room = *(t_lem**)ft_vat(sup->farm, i);
		if (room->room_status == 1)
		{
			paths = ft_vnew(sup->farm->size, sizeof(t_vec*));
			q = ft_qnew(sup->farm->size * 2, sizeof(t_vec*));
			bfs(room, paths, q);
			break;
		}
	}
}
