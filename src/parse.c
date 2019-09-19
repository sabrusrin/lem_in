/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:47 by chermist          #+#    #+#             */
/*   Updated: 2019/09/19 08:23:58 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		rooms_valid(char **tmp, char *str, t_support *sup)
{
	int i;

	i = 0;
	while (tmp[0][i])
		if (!(ft_isdigit(tmp[0][i++])) && tmp[0][0]
				!= '#' && !ft_strstr(tmp[0], "-"))
			ft_alarm(str, tmp, sup);
	if (tmp[0][0] != '#' && !(ft_strstr(tmp[0], "-")))
		return (1);
	else if (ft_strstr(tmp[0], "-"))
		return (5);
	else if (ft_strstr(tmp[0], "##end") && !tmp[0][5])
		return (4);
	else if (ft_strstr(tmp[0], "##start") && !tmp[0][7])
		return (3);
	else
		ft_alarm(str, tmp, sup);
	return (0);
}

int		command_valid(char *str, t_support *sup)
{//make four lines shorter
	char	**tmp;
	int		i;
	int		arr;

	i = 0;
	arr = 0;
	if (str[0] == '#' && str[1] != '#')
		return (6);
	tmp = ft_strsplit(str, ' ');
	while (tmp[i++])
		arr++;
	if (!arr || !tmp[0] || arr == 2 || arr > 3 ||
		(arr == 3 && (tmp[0][0] == '#' || tmp[0][0] == 'L')))
		ft_alarm(str, tmp, sup);
	if (arr == 1)
		i = rooms_valid(tmp, str, sup);
	else if (arr == 3 && !(i = 0))
	{
		while (tmp[1][i])
			if (!(ft_isdigit(tmp[1][i++])))
				ft_alarm(str, tmp, sup);
		i = 0;
		while (tmp[2][i])
			if (!(ft_isdigit(tmp[2][i++])))
				ft_alarm(str, tmp, sup);
		i = 2;
	}
	del_valid_arr(tmp);
	return (i);
}

t_lem	*make_room(char *str, t_support *sup)
{
	t_lem	*room;
	t_lem	*vat;
	char	**tmp;
	int		i;

	i = -1;
	if (!(room = ft_memalloc(sizeof(t_lem))))
		ft_alarm(str, tmp, sup);
	if (!(room->tubes = ft_vnew(5, sizeof(t_lem*))))
		ft_alarm(str, tmp, sup);
	tmp = ft_strsplit(str, ' ');
	while (sup->farm->size > ++i && (vat = ((t_lem*)ft_vat(sup->farm, i))))
		if (!(ft_strcmp(vat->name, tmp[0])) || (vat->x_coor == ft_atoi(tmp[1])
			&& (vat->y_coor == ft_atoi(tmp[2]))))
			ft_alarm(str, tmp, sup);
	room->name = ft_strdup(tmp[0]);
	room->x_coor = ft_atoi(tmp[1]);
	room->y_coor = ft_atoi(tmp[2]);
	room->room_status = 0;
	room->mark = WHITE;
	del_valid_arr(tmp);
	return (room);
}

t_lem	*make_important_room(int status, t_support *sup)
{
	t_lem	*room;
	char	*str;

	get_next_line(0, &str);
	if (command_valid(str, sup) == 2)
	{
		room = make_room(str, sup);
		if (status == 1)
		{
			room->room_status = 1;
			sup->start_mark++;
		}
		else if (status == 2)
		{
			room->room_status = 2;
			sup->end_mark++;
		}
		ft_strdel(&str);
		return (room);
	}
	else
		ft_alarm(str, NULL, sup);
	ft_strdel(&str);
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
		ft_alarm(str, tmp, sup);
	while (sup->farm->size > ++i && connect != 2)
	{
		vat = *(t_lem**)ft_vat(sup->farm, i);
		if (!(ft_strcmp(vat->name, tmp[0])) && ++connect)
			bend[0] = vat;
		if (!(ft_strcmp(vat->name, tmp[1])) && ++connect)
			bend[1] = vat;
	}
	if ((i = -1) && connect != 2)
		ft_alarm(str, tmp, sup);
	tube_connect(bend[0], bend[1]);
//	ft_vpush_back(bend[0]->tubes, &bend[1], sizeof(t_lem*));
//	ft_vpush_back(bend[1]->tubes, &bend[0], sizeof(t_lem*));
	del_valid_arr(tmp);
	return (1);
}
