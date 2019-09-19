/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qfront.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:55:11 by chermist          #+#    #+#             */
/*   Updated: 2019/09/19 00:40:51 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	*ft_qfront(t_queue *queue)
{
	if (ft_qempty(queue))
		return (NULL);
	return ((void*)&queue->data[queue->front * queue->type_sz]);
}