/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:29 by chermist          #+#    #+#             */
/*   Updated: 2019/09/20 02:52:40 by chermist         ###   ########.fr       */
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
	t_vec	*item;
	t_lem	*room;
	t_lem	*ret;
	int		i;
	int		j;

	path = ft_vnew(5, sizeof(t_lem*));
	ft_vpush_back(path, &start, sizeof(t_lem*));
	ft_qpush(q, &path);
	printf("&%p&\n", (char*)ft_qfront(q));
	while (!ft_qempty(q))
	{
		path = *(t_vec**)ft_qpop(q);
//path = *(t_vec**)ft_qpop(q);
	//	printf("2: %p   \n", path);
		start = *(t_lem**)ft_vback(path);
		printf("\n[%s]->", start->name);
		start->mark = BLACK;
		if (start->room_status == 2)
			print_path(path);
		i = -1;
		while (++i < start->tubes->size)
		{
			//when a crossroad met span a tree 
			room = *(t_lem**)ft_vat(start->tubes, i);
			if (room->mark == WHITE || room->room_status == 2)
			{
			printf("|%s|\n", room->name);
				newpath = ft_vdup(path);
				ft_vpush_back(newpath, &room, sizeof(t_lem*));		
				ft_qpush(q, &newpath);// problem is here, for some reason newpath being pushed incorrectly
				printf("rear: %d\n", (int)q->rear);
				
				t_lem	*tmp;///
				newpath = *(t_vec**)ft_qback(q);
				j = -1;
				printf("{BACK\n");
				printf("&%p&\n", (char*)ft_qback(q));
				while (++j < newpath->size)
				{
					tmp = *(t_lem**)ft_vat(newpath, j);
					printf("%s->", tmp->name);

				}
				printf("}\n");///
				newpath = *(t_vec**)ft_qfront(q);
				j = -1;
				printf("[FRONT\n");
				printf("&%p&\n", (char*)ft_qfront(q));
				while (++j < newpath->size)
				{
					tmp = *(t_lem**)ft_vat(newpath, j);
					printf("%s->", tmp->name);

				}
				printf("]\n");///

//				printf("1: %p   \n", newpath);
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
			paths = ft_vnew(sup->farm->size, sizeof(t_lem*));
			q = ft_qnew(sup->farm->size * 2, sizeof(t_vec*));
			bfs(room, paths, q);
			break;
		}
	}
}
