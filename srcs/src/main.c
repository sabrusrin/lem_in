/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:39 by chermist          #+#    #+#             */
/*   Updated: 2019/09/14 02:14:18 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

int		rooms_valid(char **tmp, char *str)
{
	int i;

	i = 0;
	while (tmp[0][i])
		if (!(ft_isdigit(tmp[0][i++])) && tmp[0][0]
				!= '#' && !ft_strstr(tmp[0], "-"))
			ft_alarm(str, tmp);
	if (tmp[0][0] != '#' && !(ft_strstr(tmp[0], "-")))
		return (1);
	else if (ft_strstr(tmp[0], "-"))
		return (5);
	else if (ft_strstr(tmp[0], "##end") && !tmp[0][5])
		return (4);
	else if (ft_strstr(tmp[0], "##start") && !tmp[0][7])
		return (3);
	else
		ft_alarm(str, tmp);
	return (0);
}

int		command_valid(char *str)
{
	char	**tmp;
	int		i;
	int		arr;

	i = 0;
	arr = 0;
	tmp = ft_strsplit(str, ' ');
	while (tmp[i++])
		arr++;
	if (!arr || !tmp[0] || arr == 2 || arr > 3 ||
			(arr == 3 && (tmp[0][0] == '#' || tmp[0][0] == 'L')))
		ft_alarm(str, tmp);
	if (arr == 1)
	{
		i = rooms_valid(tmp, str);
		del_valid_arr(tmp);
		return (i);
	}
	if (arr == 3 && !(i = 0))
	{
		while (tmp[1][i])
			if (!(ft_isdigit(tmp[1][i++])))
				ft_alarm(str, tmp);
		i = 0;
		while (tmp[2][i])
			if (!(ft_isdigit(tmp[2][i++])))
				ft_alarm(str, tmp);
		del_valid_arr(tmp);
		return (2);
	}
	return (0);
}

t_lem	*make_room(char *str, t_support *sup)
{
	t_lem	*room;
	t_lem	*vat;
	char	**tmp;
	int		i;

	i = -1;
	if (!(room = ft_memalloc(sizeof(t_lem))))
		exit(0);
	if (!(room->tubes = ft_vnew(5, sizeof(t_lem*))))
		exit(0);
	printf("size: %d\n", (int)room->tubes->capacity);
	tmp = ft_strsplit(str, ' ');
	//printf("%p________\n", room->tubes[0]);
	while (sup->farm->size > ++i)
	{
		vat = ((t_lem*)ft_vat(sup->farm, i));
		if (!(ft_strcmp(vat->name, tmp[0])) || (vat->x_coor == ft_atoi(tmp[1])
			&& (vat->y_coor == ft_atoi(tmp[2]))))
			ft_alarm(str, tmp);
	}
	room->name = tmp[0];
	tmp[0] = NULL;
	room->x_coor = ft_atoi(tmp[1]);
	room->y_coor = ft_atoi(tmp[2]);
	room->room_status = 0;
	del_valid_arr(tmp);
	return (room);
}

t_lem	*make_important_room(char *str, int status, t_support *sup)
{
	t_lem	*room;

	if (str)
		ft_strdel(&str);
	(get_next_line(0, &str));
	if (command_valid(str) == 2)
	{
		room = make_room(str, sup);
		if (status == 1)
		{
			room->room_status = 1;
			sup->start_mark++;
		}
		else
		{
			room->room_status = 2;
			sup->end_mark++;
		}
		return (room);
	}
	else
		ft_alarm(str, NULL);
	return (NULL);
}

void	delete_farm(t_lem **farm)
{
}

int		make_tube(char *str, t_support *sup)
{
	char	**tmp;
	int		i;
	t_lem	*start;
	t_lem	*end;
	int		connect;

	connect = 0;
	tmp = ft_strsplit(str, '-');
	if ((i = -1) && !*(&tmp + 2))
		ft_alarm(str, tmp);
	while (sup->farm->size > ++i && connect != 2)
	{
//		printf("cmp: %s\n", ((t_lem*)ft_vat(sup->farm, i))->name);
		if (!(ft_strcmp(((t_lem*)ft_vat(sup->farm, i))->name, tmp[0])) && ++connect)
			start = (t_lem*)ft_vat(sup->farm, i);
		if (!(ft_strcmp(((t_lem*)ft_vat(sup->farm, i))->name, tmp[1])) && ++connect)
			end = (t_lem*)ft_vat(sup->farm, i);
	}
	printf("cmp: %s -- %s, %p\n", start->name, end->name, (t_lem*)(start->tubes->data));
	if ((i = -1) && connect != 2)
		ft_alarm(str, tmp);  //уничтожить все гавно? Или природа сама разберется? (sup->farm)
//	while (start->tubes[++i])//тут нужен будет вектор
	ft_vpush_back(start->tubes, end, sizeof(t_lem*));

	printf("size: %d\n", (int)sup->farm->size);
//	printf("room: %s\n", ((t_lem*)ft_vback(start->tubes))->name);
	del_valid_arr(tmp);
	return (1);
}

void	rooms_valid_block(char *str, t_support *sup)
{
	int i;
	t_lem *room;

	i = 0;
	while (get_next_line(0, &str))
	{
		if (command_valid(str) == 2)
		{
			room = make_room(str, sup);
			ft_vpush_back(sup->farm, room, sizeof(t_lem*));
			printf("size: %d\n", (int)room->tubes->capacity);
//			printf("size: %d\n", (int)sup->farm->capacity);
			printf("room2: %s\n", ((t_lem*)ft_vback(sup->farm))->name);
		}
		else if (command_valid(str) == 3)
		{
			ft_vpush_back(sup->farm, make_important_room(str, 1, sup), sizeof(t_lem*));
			printf("room3: %s\n", ((t_lem*)ft_vback(sup->farm))->name);
		}
		else if (command_valid(str) == 4)
		{
			ft_vpush_back(sup->farm, make_important_room(str, 2, sup), sizeof(t_lem*));
			printf("room4: %s\n", ((t_lem*)ft_vback(sup->farm))->name);
		}
		else if (command_valid(str) == 5)
		{
			if (sup->start_mark != 1 || sup->end_mark != 1)
				ft_alarm(str, NULL);
			make_tube(str, sup);
			if (str)
				ft_strdel(&str);
			break ;
		}
		else
			ft_alarm(str, NULL);
		if (str)
			ft_strdel(&str);
	}
}

t_lem	*tree_make(t_support *sup)
{
	char	*str;
	int		i;

	i = 0;
	get_next_line(0, &str);
	if (command_valid(str) == 1)
		sup->ants = atoi(str);
	else
		ft_alarm(str, NULL);
	if (str)
		ft_strdel(&str);
	rooms_valid_block(str, sup);
	ft_putstr("###################\n");
	while (get_next_line(0, &str))
	{
		if (command_valid(str) == 5)
			make_tube(str, sup);
		else
			ft_alarm(str, NULL);
		if (str)
			ft_strdel(&str);
	}
	return (NULL);
}

int		main(void)
{
	t_lem		*start;
	t_support	*sup;
	t_lem		*tmp;
	int			i;
	int			i2;

	i = -1;
	sup = support_struct_init();
	ft_putstr("1here it is\n");
	start = tree_make(sup);
	printf("sup: %d\n", (int)sup->farm->size);
	while (sup->farm->size > ++i && (i2 = -1))
	{
		tmp = (t_lem*)ft_vat(sup->farm, i);
		printf("tubes: %d\n", (int)tmp->tubes->size);
		while (tmp->tubes->size > ++i2)
		{
			ft_putstr("here it is\n");
			printf("%s-%s\n", tmp->name,
					((t_lem*)ft_vat(tmp->tubes, i2))->name);
		}
	}
/*	while (sup->farm[++i] && (i2 = -1))
	{
		while (sup->farm[i]->tubes[++i2])
			printf("%s-%s\n", sup->farm[i]->name,
					sup->farm[i]->tubes[i2]->name);
	}*/
//	path_find()
	return (0);
}
