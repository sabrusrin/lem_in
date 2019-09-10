/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vnew.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:51:46 by chermist          #+#    #+#             */
/*   Updated: 2019/09/10 17:43:42 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"vector.h"

t_vec	*ft_vnew(size_t size, size_t type_sz)
{
	t_vec	*v;

	v = NULL;
	if (size && type_sz && (v = (t_vec*)malloc(sizeof(t_vec))))
	{
		v->type_sz = type_sz;
		v->capacity = 0;
		v->size = size;
		if (!(v->data = malloc(size * type_sz)))
			ft_memdel((void**)&v);
	}
	return (v);
}
