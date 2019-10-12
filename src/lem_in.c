/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:34 by chermist          #+#    #+#             */
/*   Updated: 2019/10/13 00:28:24 by chermist         ###   ########.fr       */
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

int		check_conflict(t_path *pack, t_vec *chk)
{
	int	i;
	int	j;
	int	k;
	t_vec	*path;
	t_lem	*r;
	t_lem	*rc;
	
	i = -1;
	while (++i < pack->paths->size)
	{
		path = *(t_vec**)ft_vat(pack->paths, i);
		j = -1;
		while (++j < path->size)
		{
			r = *(t_lem**)ft_vat(path, j);
			k = -1;
			while (++k < chk->size)
			{
				rc = *(t_lem**)ft_vat(chk, k);
				if (r == rc && 
					!((r->status == 1 && rc->status == 1) ||
					(r->status == 2 && rc->status == 2)))
					return (0);
			}
		}
	}
	return (1);
}
int		find_packs(t_vec *flows, t_vec *paths, t_support *sup)
{
	int		i;
	int		j;
	int		minf;
	int		minn;
	t_vec	*path;
	t_vec	*chk;
	t_path	*pack;

	i = -1;
	minf = 0;
	while (++i < paths->size)
	{
		ft_printf("&");
		path = *(t_vec**)ft_vat(paths, i);
//		print_path(path);
		pack = malloc(sizeof(t_path));
		pack->flow = path->size - 1;
		pack->num = 1;
		pack->paths = ft_vnew(20, sizeof(t_vec*));
		ft_vpush_back(pack->paths, &path, sizeof(t_vec*));
		j = 0;
		minf = 0;
		while (++j < paths->size)
		{
			chk = *(t_vec**)ft_vat(paths, j);
			//check for crossintersection in paths found
			if (check_conflict(pack, chk))
			{
//			print_path(chk);
				pack->flow += chk->size - 1;
				pack->num += 1;
				pack->pflow = pack->flow / pack->num +
					(sup->ants - pack->num) / pack->num;
//					ft_printf("^%d^", pack->pflow);
				ft_vpush_back(pack->paths, &chk, sizeof(t_vec*));
				//if found an unintersecting path => create a new pack duplicating
				//prev pack->paths, so we would have packs in ascending order
			}
		}
//		else
//			pack->pflow = 0;
//		ft_printf("|%d|\n", minf);
		ft_vpush_back(flows, &pack, sizeof(t_path*));
	//	ft_printf("%d \n", pack->flow);
	}

	return (0);
}

void	chk_pack(t_vec *p);

void	deal_conflict(t_support *sup, t_vec *paths)
{
	t_vec *flows;
	t_vec *path;
	t_vec *p;
	t_path	*packs;
	int		i;
	int		flow;

	flows = NULL;
	p = NULL;
	if (sup->ants == 1 || paths->size == 1)
	{
		use_shortest(sup, paths);
		return ;
	}
	else
	{
		flows = ft_vnew(paths->size, sizeof(t_path*));
		find_packs(flows, paths, sup);
		flow = 0;
		i = -1;
		while (++i < flows->size)
		{
			packs = *(t_path**)ft_vat(flows, i);
			if ((!flow || packs->pflow < flow) && packs->pflow)
			{
				p = packs->paths;
				flow = packs->pflow;
			}
		}
		i = -1;
		if (p)
		{
			i = -1;
			//I have a pack of unintersecting paths, do I need all of them?
//			chk_pack(p);
			ft_printf("*\n");
			while (++i < p->size)
			{
				path = *(t_vec**)ft_vat(p, i);
				print_path(path);
			}
			ft_printf("*");
		}
	}
//	find all min_val unintersecting paths
}

void	chk_pack(t_vec *p)
{

}
/*
 				if (!minf || (minf > pack->pflow && pack->pflow))
				{
					minf = pack->pflow;
					minn = pack->num;
				}
				else
					break;
//				if (minf && minf < pack->pflow)
//				{
//					ft_printf("^%d^", pack->pflow);
//					pack->pflow = 0;
//					break;
//				}
*/
