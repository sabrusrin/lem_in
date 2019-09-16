/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:42:03 by lkarlon-          #+#    #+#             */
/*   Updated: 2019/09/17 01:27:57 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		del_farm(t_support *sup)
{
	t_lem	*room;
	int		i;

	if (sup)
	{
		i = -1;
		while (++i < sup->farm->size)
			if ((room = *(t_lem**)ft_vat(sup->farm, i)))
			{
				ft_vdel(&room->tubes);
				if (room->name)
					ft_strdel(&room->name);
				ft_memdel((void**)&room);
			}
		ft_vdel(&sup->farm);
		ft_memdel((void**)&sup);
	}
}

t_support	*support_struct_init(void)
{
	t_support *sup;

	if (!(sup = ft_memalloc(sizeof(t_support))))
		exit(1);
	if (!(sup->farm = ft_vnew(25, sizeof(t_lem*))))
	{
		ft_memdel((void**)&sup);
		exit(1);
	}
	sup->start_mark = 0;
	sup->end_mark = 0;
	return (sup);
}

void		del_valid_arr(char **valid_arr)
{
	int y;

	y = 0;
	if (valid_arr && *valid_arr)
		while (valid_arr[y])
			ft_strdel(&(valid_arr[y++]));
	if (valid_arr)
		free(valid_arr);
	valid_arr = NULL;
}

void		ft_alarm(char *str, char **valid_arr, t_support *sup)
{
	del_farm(sup);
	if (valid_arr)
		del_valid_arr(valid_arr);
	ft_strdel(&str);
	write(1, "ERROR\n", 6);
	exit(0);
}
