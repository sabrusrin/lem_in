/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:34 by chermist          #+#    #+#             */
/*   Updated: 2019/10/20 23:46:44 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clean_all(t_vec *flows)
{
	int		i;
	t_path	*pack;

	if (flows)
	{
		i = -1;
		while (++i < flows->size)
		{
			pack = *(t_path**)ft_vat(flows, i);
			ft_vdel(&pack->paths);
			ft_memdel((void**)&pack);
		}
		ft_vdel(&flows);
	}
}

int		check_conflict(t_path *pack, t_vec *chk)
{
	int	i[3];
	t_vec	*path;
	t_lem	*r;
	t_lem	*rc;
	
	i[0] = -1;
	while (++i[0] < pack->paths->size && (i[1] = -1))
	{
		path = *(t_vec**)ft_vat(pack->paths, i[0]);
		while (++i[1] < path->size && (i[2] = -1))
		{
			r = *(t_lem**)ft_vat(path, i[1]);
			while (++i[2] < chk->size)
			{
				rc = *(t_lem**)ft_vat(chk, i[2]);
				if ((r == rc && 
					!((r->status == 1 && rc->status == 1) ||
					(r->status == 2 && rc->status == 2))) ||
					chk == path)
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
	t_vec	*path;
	t_vec	*chk;
	t_path	*pack;

	i = -1;
	while (++i < paths->size)
	{
		path = *(t_vec**)ft_vat(paths, i);
		pack = malloc(sizeof(t_path));
		pack->flow = path->size - 1;
		pack->num = 1;
		pack->pflow = pack->flow / pack->num +
			(sup->ants - pack->num) / pack->num;
		pack->paths = ft_vnew(20, sizeof(t_vec*));
		ft_vpush_back(pack->paths, &path, sizeof(t_vec*));
		j = -1;
		while (++j < paths->size)
		{
			chk = *(t_vec**)ft_vat(paths, j);
			if (check_conflict(pack, chk))
			{
				pack->flow += chk->size - 1;
				pack->num += 1;
				pack->pflow = pack->flow / pack->num +
					(sup->ants - pack->num) / pack->num;
				ft_vpush_back(pack->paths, &chk, sizeof(t_vec*));
			}
		}
		ft_vpush_back(flows, &pack, sizeof(t_path*));
	}
	return (0);
}

void	lem_in(t_support *sup, t_vec *paths)
{
	t_vec	*flows;
	t_path	*packs;
	int		i[2];
	int		flow;

	flows = ft_vnew(paths->size, sizeof(t_path*));
	find_packs(flows, paths, sup);
	flow = 0;
	i[0] = -1;
	i[1] = 0;
	while (++i[0] < flows->size)
	{
		packs = *(t_path**)ft_vat(flows, i[0]);
		if ((!flow || packs->pflow < flow) && packs->pflow)
		{
			i[1] = i[0];
			flow = packs->pflow;
		}
	}
	packs = *(t_path**)ft_vat(flows, i[1]);
	if (packs)
		print_moves(packs->paths, sup);
	clean_all(flows);
}

/*
 	if (p)
	{
		i = -1;
		while (++i < p->size)
		{
			path = *(t_vec**)ft_vat(p, i);
			print_path(path);
		}
	}
 
 */
