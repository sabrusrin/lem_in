/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:47 by chermist          #+#    #+#             */
/*   Updated: 2019/11/03 18:19:29 by lkarlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		rooms_valid(char **tmp, t_support *sup)
{
	int i;

	i = 0;
	while (tmp[0][i])
		if (!(ft_isdigit(tmp[0][i++])) && tmp[0][0] != '#' &&
		!ft_strstr(tmp[0], "-"))
			ft_alarm(tmp, sup);
	if (tmp[0][0] != '#' && !(ft_strstr(tmp[0], "-")))
		return (1);
	else if (ft_strstr(tmp[0], "-"))
		return (5);
	else if (ft_strstr(tmp[0], "##end") && !tmp[0][5])
		return (4);
	else if (ft_strstr(tmp[0], "##start") && !tmp[0][7])
		return (3);
	else
		ft_alarm(tmp, sup);
	return (0);
}

int		command_valid(char *str, t_support *sup, int i, int a)
{
	char	**tmp;

	if (str[0] == '#' && !(ft_strstr(str, "##end")) &&
			!(ft_strstr(str, "##start")))
		return (6);
	tmp = ft_strsplit(str, ' ');
	while (tmp[i++])
		a++;
	if (!a || !tmp[0] || a == 2 || a > 3 || (a == 3 && (tmp[0][0] == 'L')))
		ft_alarm(tmp, sup);
	if (a == 1)
		i = rooms_valid(tmp, sup);
	else if (a == 3 && !(i = 0))
	{
		while (tmp[1][i])
			if (!(ft_isdigit(tmp[1][i++])) && !(tmp[1][0] = '-' && i == 1))
				ft_alarm(tmp, sup);
		i = 0;
		while (tmp[2][i])
			if (!(ft_isdigit(tmp[2][i++])) && !(tmp[2][0] = '-' && i == 1))
				ft_alarm(tmp, sup);
		i = 2;
	}
	del_valid_arr(tmp);
	return (i);
}

t_lem	*make_room(char *str, t_support *sup)
{
	t_lem		*room;
	t_lem		*vat;
	char		**tmp;
	int			i;

	i = -1;
	tmp = ft_strsplit(str, ' ');
	if (!(room = ft_memalloc(sizeof(t_lem))))
		ft_alarm(tmp, sup);
	if (!(room->tubes = ft_vnew(5, sizeof(t_lem*))))
		ft_alarm(tmp, sup);
	while ((int)sup->farm->size > ++i && (vat = *(t_lem**)ft_vat(sup->farm, i)))
		if (ft_strequ(vat->name, tmp[0]))
			ft_alarm(tmp, sup);
	room->name = ft_strdup(tmp[0]);
	room->x = (int)ft_fabs(ft_atoi(tmp[1]));
	room->y = (int)ft_fabs(ft_atoi(tmp[2]));
	compare_coords(sup, room->x, room->y);
	room->status = 0;
	room->mark = 0;
	del_valid_arr(tmp);
	return (room);
}

t_lem	*make_important_room(int status, t_support *sup)
{
	t_lem	*room;
	char	*str;

	get_next_line(0, &str);
	ft_vpush_back(sup->in, &str, sizeof(char*));
	if (command_valid(str, sup, 0, 0) == 2)
	{
		if ((room = make_room(str, sup)))
		{
			if (status == 1)
			{
				room->status = 1;
				sup->start_mark++;
			}
			else if (status == 2)
			{
				room->status = 2;
				sup->end_mark++;
			}
			return (room);
		}
	}
	else
		ft_alarm(NULL, sup);
	return (NULL);
}

int		make_tube(char *str, t_support *sup)
{
	char	**tmp;
	int		i;
	t_lem	*bend[2];
	t_lem	*vat;
	int		connect;

	connect = 0;
	tmp = ft_strsplit(str, '-');
	if ((i = -1) && !*(&tmp + 2))
		ft_alarm(tmp, sup);
	while ((int)sup->farm->size > ++i && connect != 2)
	{
		vat = *(t_lem**)ft_vat(sup->farm, i);
		if (!(ft_strcmp(vat->name, tmp[0])) && ++connect)
			bend[0] = vat;
		if (!(ft_strcmp(vat->name, tmp[1])) && ++connect)
			bend[1] = vat;
	}
	if ((i = -1) && connect != 2)
		ft_alarm(tmp, sup);
	tube_connect(bend[0], bend[1], sup);
	del_valid_arr(tmp);
	return (1);
}
