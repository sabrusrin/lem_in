/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 12:24:14 by chermist          #+#    #+#             */
/*   Updated: 2019/10/26 12:31:54 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_weight(t_vec *paths, t_vec *path, int j, int ants)
{
	t_vec	*p;
	int		flow;
	int		pflow;
	int		minf;
	int		i;

	minf = 0;
	i = -1;
	flow = 0;
	while (++i <= j)
	{
		p = *(t_vec**)ft_vat(paths, i);
		flow += p->size - 1;
		i++;
		pflow = ((flow - i) + (ants - i)) / i;
		i--;
		if (!minf || (minf > pflow))
			minf = pflow;
		if (pflow > minf && p == path)
		{
			return (0);
		}
	}
	return (1);
}
