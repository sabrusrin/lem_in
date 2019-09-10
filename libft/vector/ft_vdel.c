/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:08:15 by chermist          #+#    #+#             */
/*   Updated: 2019/09/10 17:30:24 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	ft_vdel(t_vec **v)
{
	ft_bzero((*v)->data, (*v)->capacity);
	ft_memdel((*v)->data);
	ft_memdel((void**)v);
}