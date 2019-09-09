/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vresize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 17:21:12 by chermist          #+#    #+#             */
/*   Updated: 2019/09/10 00:15:24 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	ft_vresize(t_vec *v, size_t size)
{
	if (v && size)	
	{
		if ((v->data = ft_realloc(&(v->data), v->size, size)))
		{
			v->size = size;
			if (v->size < v->count * v->type_sz)
				v->count = v->size / v->type_sz;
		}
	}
}
