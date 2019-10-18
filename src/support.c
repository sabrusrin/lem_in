/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:42:03 by lkarlon-          #+#    #+#             */
/*   Updated: 2019/10/18 23:44:46 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		del_farm(t_support *sup)
{
	t_lem	*room;
	char	*str;
	int		i;

	if (sup && (i = -1))
	{
		while (++i < sup->farm->size)
			if ((room = *(t_lem**)ft_vat(sup->farm, i)))
			{
				ft_vdel(&room->tubes);
				if (room->name)
					ft_strdel(&room->name);
				ft_memdel((void**)&room);
			}
		if (sup->opt.nomap && (i = -1))
		{
			while (++i < sup->in->size &&
				(str = *(char**)ft_vat(sup->in, i)))	
				ft_strdel(&str);
			ft_vdel(&sup->in);
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
	if (!(sup->farm = ft_vnew(100, sizeof(t_lem*))))
	{
		ft_memdel((void**)&sup);
		exit(1);
	}
	if (!(sup->in = ft_vnew(500, sizeof(char*))))
	{
		ft_memdel((void**)&sup);
		ft_vdel(&sup->farm);
		exit(1);
	}
	sup->start_mark = 0;
	sup->end_mark = 0;
	return (sup);
}

int			check_id(char *str, t_support *sup)
{
	int		i;
	t_lem	*room;

	i = -1;
	while (++i < sup->farm->size)
	{
		room = *(t_lem**)ft_vat(sup->farm, i);
		if (ft_strstr(str, room->name))
			return (0);
	}
	return (1);
}

void		tube_connect(t_lem *start, t_lem *end)
{
	int		i;
	int		con;
	t_lem	*room;

	ft_vpush_back(start->tubes, &end, sizeof(t_lem*));
	i = -1;
	con = 1;
	while (++i < end->tubes->size)
	{
		room = *(t_lem**)ft_vat(end->tubes, i);
		if (ft_strstr(start->name, room->name))
		{
			con = 0;
			break;
		}
	}
	if (con)
		ft_vpush_back(end->tubes, &start, sizeof(t_lem*));
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

void		ft_alarm(char **valid_arr, t_support *sup)
{
	sup->opt.nomap = 1;
	del_farm(sup);
	if (valid_arr)
		del_valid_arr(valid_arr);
	write(1, "ERROR\n", 6);
	exit(0);
}
