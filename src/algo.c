/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:29 by chermist          #+#    #+#             */
/*   Updated: 2019/09/19 08:23:53 by chermist         ###   ########.fr       */
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
		printf("%s->", tmp->name);
	}
	printf("\n");
}

void	bfs(t_lem *start, t_vec *paths, t_queue *q)
{
	t_vec	*path;
	t_vec	*newpath;
	t_vec	*item;
	t_lem	*room;
	t_lem	*ret;
	int		i;
	int		j;
	//int		last;

//	printf("KAKA\n");
	path = ft_vnew(5, sizeof(t_lem*));
//	q = ft_qnew(sup->farm->size, sizeof(t_vec*));
	ft_vpush_back(path, &start, sizeof(t_lem*));
	ft_qpush(q, &path);
	printf("1: %p   \n", path);
	//while (!(ft_qempty(q)))
	while (!ft_qempty(q))
	{
		path = *(t_vec**)ft_qfront(q);
		printf("2: %p   \n", path);
		item = *(t_vec**)ft_qpop(q);
		printf("3: %p   \n", item);
//	QUEUE DOESN'T WORK CORRECTLY
		start = *(t_lem**)ft_vat(path, 0);
		printf("[%s   %d]\n", start->name, start->mark);
		start->mark = BLACK;
		ft_qpop(q);
//		start = *(t_lem**)ft_vat()
//		room = path
//		printf("|%s|\n", start->name);
//		if (start->room_status == 2)
			print_path(path);
		i = -1;
		while (++i < start->tubes->size)
		{
			//when a crossroad met span a tree 
			room = *(t_lem**)ft_vat(start->tubes, i);
			if (room->mark != BLACK)
			{
			printf("|%s   %d|\n", room->name, room->mark);
				path = ft_vnew(5, sizeof(t_lem*));
				ft_vpush_back(path, &room, sizeof(t_lem*));		
				ft_qpush(q, &path);
				printf("1: %p   \n", path);
				room->mark = GRAY;
			}
		}
	}
	/*
	i = -1;
	start->mark = BLACK;
	path = ft_vnew(5, sizeof(t_lem*));
//	printf("%s   %d\n", start->name, (int)start->tubes->size);
	while (++i < start->tubes->size)
	{
		j = -1;
		while (++j < start->tubes->size)
		{
			room = *(t_lem**)ft_vat(start->tubes, j);
			if (room->mark == WHITE)
				room->mark = GRAY;
		}
		room = *(t_lem**)ft_vat(start->tubes, i);
		if (room->room_status == 2)
			return (room);// save path
		else if (room->mark != BLACK)
		{
			printf("%s->", room->name);
			ret = bfs(room, paths, q);
			if (room->tubes->size > 1)
			{
				room->mark = GRAY;
				printf("\n");
				continue;
			}
			else if (ret && ret->room_status != 1)
			{
				printf("%s<-", ret->name);
				return (room);
			}
			else
				printf("none");
			if (start->room_status == 1)
				printf("\n");
		}
	}
	return (NULL);*/
}

void	path_find(t_support *sup)
{
	t_lem	*room;
	t_vec	*paths;
	t_queue	*q;
//	t_list	*queue
	int		i;

	i = -1;
	while (++i < sup->farm->size)
	{
		room = *(t_lem**)ft_vat(sup->farm, i);
		if (room->room_status == 1)
		{
//			printf("%s ", room->name);
			ft_putstr(room->name);
			room->mark = BLACK;
			paths = ft_vnew(sup->farm->size, sizeof(t_lem*));
			q = ft_qnew(sup->farm->size, sizeof(t_vec*));
			bfs(room, paths, q);
			break;
		}
	}
}
