/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:50:26 by chermist          #+#    #+#             */
/*   Updated: 2019/09/10 18:03:45 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include "libft.h"
// Functions:
//
//    vector::max_size - Returns maximum number of elements vector could
//                       hold.
//
//    vector::capacity - Returns number of elements for which memory has
//                       been allocated.
//
//    vector::size - Returns number of elements in the vector.
//
//    vector::resize - Reallocates memory for vector, preserves its
//                     contents if new size is larger than existing size.
//
//    vector::reserve - Allocates elements for vector to ensure a minimum
//                      size, preserving its contents if the new size is
//                      larger than existing size.
//
//    vector::push_back - Appends (inserts) an element to the end of a
//                        vector, allocating memory for it if necessary.

typedef struct	s_vec
{
	void		*data;
	size_t		size; // number of elements currently stored in the vector
	size_t		capacity; // max num of elem that vector can store without rellocation
	size_t		type_sz; // size of data type
}				t_vec;

t_vec			*ft_vnew(size_t size, size_t type_sz);
void			ft_vresize(t_vec *v, size_t size);
void			ft_vpush_back(t_vec *v, void *val, size_t val_sz);
void			*ft_vat(t_vec *v, size_t at);
void			ft_vdel(t_vec **v);

#endif
