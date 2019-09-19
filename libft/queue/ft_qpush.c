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

void	ft_qpush(t_queue *queue, void *item)
{
	if (ft_qfull(queue))
		return ;
	queue->rear = (queue->rear + 1) % queue->capacity;
//	printf("^%d %d^\n", queue->rear, (int)queue->type_sz);
	ft_memmove(&queue->data[queue->rear * queue->type_sz],
			item, queue->type_sz);
//	printf("|%p|\n",&queue->data[queue->rear * queue->type_sz]);
	queue->size += 1;
}
