/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:42:03 by lkarlon-          #+#    #+#             */
/*   Updated: 2019/09/14 21:35:02 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_support *support_struct_init(void)
{
	t_support *sup;

	if (!(sup = ft_memalloc(sizeof(t_support))))
		exit(1);
	if (!(sup->farm = ft_vnew(25, sizeof(t_lem*))))
		exit(1);
//	if (!(sup->farm = ft_memalloc(sizeof(t_lem) * 100)))
//		exit(1);
	sup->start_mark = 0;
	sup->end_mark = 0;
	return (sup);
}

void	del_valid_arr(char **valid_arr)
{
	int y;

	y = -1;
	if (valid_arr)
		while (valid_arr[++y])
		{
			if (valid_arr[y])
				ft_strdel(&(valid_arr[y]));
		}
	if (valid_arr)
		free(valid_arr);
	valid_arr = NULL;
}

void ft_alarm (char *str, char **valid_arr)
{
	if (valid_arr)
		del_valid_arr(valid_arr);
	if (str)
		ft_strdel(&str);
	write(1, "ERROR\n", 6);
	exit(0);
}
