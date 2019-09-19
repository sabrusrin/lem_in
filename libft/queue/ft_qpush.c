/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qpush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:15:12 by chermist          #+#    #+#             */
/*   Updated: 2019/09/19 00:40:00 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	ft_qpush(t_queue *queue, void *item)
{
	if (ft_qfull(queue))
		return ;
	queue->rear = (queue->rear + 1) % queue->capacity;
	ft_memmove(&queue->data[queue->rear * queue->type_sz],
			item, queue->type_sz);
	queue->size += 1;
}
