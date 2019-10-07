/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:29 by chermist          #+#    #+#             */
/*   Updated: 2019/10/07 21:55:04 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "stdio.h"

void	print_in(t_support *sup)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < sup->in->size)	
	{
		str = *(char**)ft_vat(sup->in, i);
		ft_putstr(str);
		ft_putchar('\n');
		ft_strdel(&str);
	}
	ft_vdel(&sup->in);
}

void	clean_up(t_vec *paths, t_queue *q)
{
	t_vec *tmp;
	int	i;

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

int		check_path(t_vec *path, t_lem *room)
{
	int i;

	i = -1;
	while (++i < path->size)
		if (room == *(t_lem**)ft_vat(path, i))
			return (0);
	return (1);
}

void	bfs(t_lem *start, t_vec *paths, t_queue *q)
{
	t_vec	*path;
	t_vec	*newpath;
	t_lem	*room;
	t_lem	*chk;
	int		i;
	int		j;

	j = 1;
	path = ft_vnew(5, sizeof(t_lem*));
	ft_vpush_back(path, &start, sizeof(t_lem*));
	ft_qpush(q, &path);
	while (!ft_qempty(q))
	{
		path = *(t_vec**)ft_qpop(q);
//		printf("POP: ");
//		print_path(path);
		start = *(t_lem**)ft_vback(path);
//		printf("\n[%s]->", start->name);
		if (start->room_status == 2)
		{
			ft_vpush_back(paths, &path, sizeof(t_vec*));
			print_path(path);
			continue;
		}
		if (j == q->capacity)
			break ;
		i = -1;
		while (++i < start->tubes->size)
		{
			room = *(t_lem**)ft_vat(start->tubes, i);
			//if (check_path(path, room))
			// check if the next room value is <= room+1, if not then use the new path
			if ((room->mark == 0 || room->mark >= start->mark
				|| start->tubes->size == 1) && check_path(path, room))
			{
				if (room->mark == 0)
					room->mark = start->mark + 1;
//				printf("|%s|%d|\n", room->name, room->mark);
				newpath = ft_vdup(path);
				ft_vpush_back(newpath, &room, sizeof(t_lem*));		
				ft_qpush(q, &newpath);
				j++;
//					printf("PUSH: ");
//					print_path(newpath);
			}
		}
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
	while (++i < sup->farm->size)
	{
		room = *(t_lem**)ft_vat(sup->farm, i);
		if (room->room_status == 1)
		{
			paths = ft_vnew(sup->farm->size, sizeof(t_vec*));
			q = ft_qnew(sup->farm->size * 2, sizeof(t_vec*));
			if (sup->opt.nomap == 0)
				print_in(sup);
			bfs(room, paths, q);
			break;
		}
	}
//	max_flow(paths);
	clean_up(paths, q);
}
