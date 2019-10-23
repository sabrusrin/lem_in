/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:42:03 by lkarlon-          #+#    #+#             */
/*   Updated: 2019/10/23 14:31:32 by chermist         ###   ########.fr       */
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
	}
}

void	support_struct_init(t_support *sup)
{
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
	sup->xy[0][0] = 0;
	sup->xy[0][1] = 0;
	sup->xy[1][0] = 0;
	sup->xy[1][1] = 0;
}

void		tube_connect(t_lem *start, t_lem *end, t_support *sup)
{
	int		i;
	int		con;
	t_lem	*room;
	t_lines	*line;

	ft_vpush_back(start->tubes, &end, sizeof(t_lem*));
	if (sup->opt.visu && (line = malloc(sizeof(t_lines*))))
	{
		line->a = start;
		line->b = end;
		ft_vpush_back(sup->lines, &line, sizeof(t_lines*));
		sup->cons += 1;
	}
	i = -1;
	con = 1;
	while (++i < end->tubes->size && (room = *(t_lem**)ft_vat(end->tubes, i)))
	{
		if (ft_strstr(start->name, room->name))
		{
			con = 0;
			break ;
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
