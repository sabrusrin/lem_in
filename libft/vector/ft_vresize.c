/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vresize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 17:21:12 by chermist          #+#    #+#             */
/*   Updated: 2019/09/10 18:03:58 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	ft_vresize(t_vec *v, size_t size)
{
	if (v && size)	
	{
		if ((v->data = ft_realloc(&(v->data), v->capacity, size)))
		{
			v->capacity = size;
			if (v->capacity < v->size * v->type_sz)
				v->size = v->capacity / v->type_sz;
		}
	}
}
