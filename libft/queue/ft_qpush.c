/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qpush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:15:12 by chermist          #+#    #+#             */
/*   Updated: 2019/09/20 02:15:39 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"
#include <stdio.h>

void	ft_qpush(t_queue *q, void *item)
{
	if (ft_qfull(q))
		return ;
	q->rear = (q->rear + 1) % q->capacity;
//	printf("^%d %d^\n", q->rear, (int)q->type_sz);
	ft_memmove((void*)&q->data[q->rear * q->type_sz],
			item, q->type_sz);
//	printf("|%p|\n",&q->data[q->rear * q->type_sz]);
	q->size += 1;
}
