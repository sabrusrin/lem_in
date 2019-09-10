/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vpush_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:51:28 by chermist          #+#    #+#             */
/*   Updated: 2019/09/10 00:15:22 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	ft_vpush_back(t_vec *v, void *val, size_t val_sz)
{
	void	*tmp;
	size_t	new_sz;

	new_sz = v->count * v->type_sz + val_sz;
	if (v && val)
	{
		if (size < new_sz)
		ft_memmove(v->data + (v->count * v->type_sz), val, val_sz);

	}
}
