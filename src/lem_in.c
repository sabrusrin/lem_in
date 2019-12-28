/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:34 by chermist          #+#    #+#             */
/*   Updated: 2019/10/26 18:24:39 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_in(t_support *sup)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < (int)sup->in->size)
	{
		str = *(char**)ft_vat(sup->in, i);
		ft_putstr(str);
		ft_putchar('\n');
		ft_strdel(&str);
	}
	ft_putchar('\n');
	ft_vdel(&sup->in);
}

void	clean_all(t_vec *flows)
{
	int		i;
	t_path	*pack;

	if (flows)
	{
		i = -1;
		while (++i < (int)flows->size)
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
	int		i[3];
	t_vec	*path;
	t_lem	*r;
	t_lem	*rc;

	i[0] = -1;
	while (++i[0] < (int)pack->paths->size && (i[1] = -1))
	{
		path = *(t_vec**)ft_vat(pack->paths, i[0]);
		while (++i[1] < (int)path->size && (i[2] = -1))
		{
			r = *(t_lem**)ft_vat(path, i[1]);
			while (++i[2] < (int)chk->size)
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
	int		i[2];
	t_vec	*path;
	t_vec	*c;
	t_path	*pack;

	i[0] = -1;
	while (++i[0] < (int)paths->size && (path = *(t_vec**)ft_vat(paths, i[0])))
	{
		if (!(pack = malloc(sizeof(t_path))) ||
			!(pack->paths = ft_vnew(3, sizeof(t_vec*))))
			return (0);
		pack->flow = path->size - 1;
		pack->pflow = pack->flow / 1 + (sup->ants - 1);
		ft_vpush_back(pack->paths, &path, sizeof(t_vec*));
		i[1] = -1;
		while (++i[1] < (int)paths->size && (c = *(t_vec**)ft_vat(paths, i[1])))
			if (check_conflict(pack, c) && (pack->flow += c->size - 1))
			{
				ft_vpush_back(pack->paths, &c, sizeof(t_vec*));
				pack->pflow = pack->flow / pack->paths->size +
					(sup->ants - pack->paths->size) / pack->paths->size;
			}
		ft_vpush_back(flows, &pack, sizeof(t_path*));
	}
	return (1);
}

void	lem_in(t_support *sup, t_vec *paths)
{
	t_vec	*flows;
	t_path	*packs;
	int		i[2];
	int		flow;

	if ((i[0] = -1) && (*(t_vec**)ft_vat(paths, 0))->size == 2)
		move_to_end(sup, *(t_vec**)ft_vat(paths, 0));
	else
	{
		flows = ft_vnew(paths->size, sizeof(t_path*));
		flow = 0;
		packs = NULL;
		if (!(i[1] = 0) && (find_packs(flows, paths, sup)))
			while (++i[0] < (int)flows->size &&
				(packs = *(t_path**)ft_vat(flows, i[0])))
				if ((!flow || packs->pflow < flow) && packs->pflow)
				{
					flow = packs->pflow;
					i[1] = i[0];
				}
		if (packs && (packs = *(t_path**)ft_vat(flows, i[1])))
			print_moves(packs->paths, sup);
		clean_all(flows);
	}
}
