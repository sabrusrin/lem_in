/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:34 by chermist          #+#    #+#             */
/*   Updated: 2019/10/12 02:11:03 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	t_vec	*path;
	t_vec	*chk;
	t_path	*pack;

	i = -1;
	while (++i < paths->size)
	{
		ft_putchar('&');
		path = *(t_vec**)ft_vat(paths, i);
		print_path(path);
		pack = malloc(sizeof(t_path));
		pack->flow = path->size - 1;
		pack->num = 1;
		pack->paths = ft_vnew(20, sizeof(t_vec*));
		ft_vpush_back(pack->paths, &path, sizeof(t_vec*));
		j = 0;
		while (++j < paths->size)
		{
			chk = *(t_vec**)ft_vat(paths, j);
			//check for crossintersection in paths found
			if (check_conflict(pack, chk))
			{
			print_path(chk);
				pack->flow += chk->size - 1;
				pack->num += 1;
				//segfault here
//	write(1, "HERE", 4);
//	ft_putnbr(j);
				ft_vpush_back(pack->paths, &chk, sizeof(t_vec*));
//	write(1, "Kaka", 4);
//	write(1, "\n", 1);
				//segfault here
				//if found an unintersecting path => create a new pack duplicating
				//prev pack->paths, so we would have packs in ascending order
			}
		}
		pack->flow = pack->flow / pack->num + (sup->ants - pack->num) / pack->num;
		ft_putnbr(pack->flow);
		ft_putstr("&\n");
	}
	return (0);
}

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

void	deal_conflict(t_support *sup, t_vec *paths)
{
	t_vec *flows;
	t_vec *path;
	t_vec *p;
	t_path	*packs;
	int		i;
	int		flow;

	flows = NULL;
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
//	write(1, "HERE", 4);
	while (++i < flows->size)
	{
		packs = *(t_path**)ft_vat(flows, i);
		if (!flow || packs->flow < flow)
		{
			p = packs->paths;
			flow = packs->flow;
		}
	}
	i = -1;
	while (++i < p->size)
	{
		path = *(t_vec**)ft_vat(p, i);
		print_path(path);
	}
	}	
//	find all min_val unintersecting paths
}
