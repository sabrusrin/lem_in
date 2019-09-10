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

int		main(void)
{
	t_vec	*vector;
	int		val;

	vector = ft_vnew(5, sizeof(int));
	
	ft_putnbr((int)vector->size);
	ft_putchar('\n');
	val = 127;
	ft_vpush_back(vector, &val, sizeof(int));
	ft_putnbr((int)ft_vat(vector, 1));
	ft_putchar('\n');
	val = 255;
	ft_vpush_back(vector, &val, sizeof(int));
	val = 511;
	ft_vpush_back(vector, &val, sizeof(int));
	val = 5;
	ft_vpush_back(vector, &val, sizeof(int));
	ft_putnbr((int)ft_vat(vector, 4));
	ft_putchar('\n');
	val = 22;
	ft_vpush_back(vector, &val, sizeof(int));
	ft_putnbr((int)ft_vat(vector, 2));
	ft_putchar('\n');
	ft_putnbr((int)ft_vat(vector, 1));
	ft_putchar('\n');

	return (0);
}
