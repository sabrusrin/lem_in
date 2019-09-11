/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:39 by chermist          #+#    #+#             */
/*   Updated: 2019/09/11 23:34:54 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"
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
	char	**tmp;
	int		i;

	i = -1;
	if (!(room = ft_memalloc(sizeof(t_lem) * 100)))
		exit(0);
	if (!(room->tubes = ft_memalloc(sizeof(t_lem*) * 10)))
		exit(0);
	tmp = ft_strsplit(str, ' ');
	while (sup->farm[++i])
	{
		if (!(ft_strcmp(sup->farm[i]->name, tmp[0])) || (sup->farm[i]->x_coor
				== ft_atoi(tmp[1]) && sup->farm[i]->y_coor == ft_atoi(tmp[2])))
			ft_alarm(str, tmp);
	}
	room->name = tmp[0];
	tmp[0] = NULL;
	room->x_coor = ft_atoi(tmp[1]);
	room->y_coor = ft_atoi(tmp[2]);
	room->room_status = 0;
	del_valid_arr(tmp);
//	ft_putchar('\n');
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
	while (sup->farm[++i] && connect != 2)
	{
		if (!(ft_strcmp(sup->farm[i]->name, tmp[0])) && ++connect)
			start = sup->farm[i];
		if (!(ft_strcmp(sup->farm[i]->name, tmp[1])) && ++connect)
			end = sup->farm[i];
	}
	if ((i = -1) && connect != 2)
		ft_alarm(str, tmp);  //уничтожить все гавно? Или природа сама разберется? (sup->farm)
	while (start->tubes[++i])//тут нужен будет вектор
		;
	start->tubes[i] = end;
	del_valid_arr(tmp);
	return (1);
}

void	rooms_valid_block(char *str, t_support *sup)
{
	int i;

	i = 0;
	while (get_next_line(0, &str))
	{
		if (command_valid(str) == 2)
			sup->farm[i++] = make_room(str, sup);
		else if (command_valid(str) == 3)
			sup->farm[i++] = make_important_room(str, 1, sup);
		else if (command_valid(str) == 4)
			sup->farm[i++] = make_important_room(str, 2, sup);
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
	int			i;
	int			i2;

	i = -1;
	sup = support_struct_init();
	start = tree_make(sup);
//	printf("%s\n", start->name);
	while (sup->farm[++i] && (i2 = -1))
	{
		while (sup->farm[i]->tubes[++i2])
			printf("%s-%s\n", sup->farm[i]->name,
					sup->farm[i]->tubes[i2]->name);
	}
//	path_find()
	return (0);
}
