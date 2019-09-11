/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:24:50 by chermist          #+#    #+#             */
/*   Updated: 2019/09/11 14:03:36 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	*ft_vat(t_vec *v, size_t at)
{
	unsigned char	*tmp;

	if (v)
	{
		tmp = v->data;
		return ((void*)&tmp[--at * v->type_sz]);
	}
	return (0);
}
