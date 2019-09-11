/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:18:01 by chermist          #+#    #+#             */
/*   Updated: 2019/09/10 18:03:40 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		main(void)
{
	t_vec	*vector;
	char		val;
	int		*res;

	vector = ft_vnew(5, sizeof(char));
	
	printf("size: %d capacity: %d\n", (int)vector->size, (int)vector->capacity);
	val = 'A';
	ft_vpush_back(vector, &val, sizeof(char));
	printf("at1: %c\n", *(char*)ft_vat(vector, 1));
	printf("size: %d capacity: %d\n", (int)vector->size, (int)vector->capacity);
	val = 'B';
	ft_vpush_back(vector, &val, sizeof(char));
	val = 'C';
	ft_vpush_back(vector, &val, sizeof(char));
	val = 'D';
	ft_vpush_back(vector, &val, sizeof(char));
	printf("at4: %c\n", *(char*)ft_vat(vector, 4));
	printf("size: %d capacity: %d\n", (int)vector->size, (int)vector->capacity);
	val = 'E';
	ft_vpush_back(vector, &val, sizeof(char));
	printf("at2: %c\n", *(char*)ft_vat(vector, 2));
	printf("size: %d capacity: %d\n", (int)vector->size, (int)vector->capacity);
	printf("at1: %c\n", *(char*)ft_vat(vector, 1));
	printf("size: %d capacity: %d\n", (int)vector->size, (int)vector->capacity);
	val = 'F';
	ft_vpush_back(vector, &val, sizeof(char));
	printf("at1: %c\n", *(char*)ft_vat(vector, 1));
	printf("at5: %c\n", *(char*)ft_vat(vector, 5));
	printf("at6: %c\n", *(char*)ft_vat(vector, 6));
	printf("size: %d capacity: %d\n", (int)vector->size, (int)vector->capacity);

	return (0);
}
