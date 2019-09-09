/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:39 by chermist          #+#    #+#             */
/*   Updated: 2019/09/08 20:34:53 by lkarlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		rooms_valid(char **tmp, char *str)
{
	int i;

	i = 0;
	while (tmp[0][i])
			if (!(ft_isdigit(tmp[0][i++])) && tmp[0][0] != '#' && tmp[0][i - 1] != '-')
				ft_alarm(str, tmp);
	if (tmp[0][0] != '#' && !(ft_strstr(tmp[0], "-")))
		return (1);
	else if (ft_strstr(tmp[0], "-") && ft_isdigit(*((ft_strstr(tmp[0], "-") - 1))) && ft_isdigit(*((ft_strstr(tmp[0], "-")) + 1)))
		return (5);
	else if (ft_strstr(tmp[0], "##end") && !tmp[0][5])
		return(4);
	else if (ft_strstr(tmp[0], "##start") && !tmp[0][7])
		return(3);
	else
		ft_alarm (str, tmp);
		return (0);
}

int		command_valid(char *str)
{
	char **tmp;
	int i;
	int arr;

	i = 0;
	arr = 0;
	tmp = ft_strsplit(str, ' ');
	while(tmp[i++])
		arr++;
	i = 0;
	if (!arr || !tmp[0] || arr == 2 || arr > 3 || (arr == 3 && (tmp[0][0] == '#' || tmp[0][0] == 'L')))
			ft_alarm(str, tmp);
	if (arr == 1)
	{
		i =	rooms_valid(tmp, str);
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
		return(2);
	}
	return(0);
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
/* 	write(1, "zdorov!\n", 8);
	ft_putstr(tmp[0]);
	ft_putchar('\n');
	ft_putstr(tmp[1]);
	ft_putchar('\n');
	ft_putstr(tmp[2]);
	ft_putchar('\n');
	write(1, "poka\n", 5); */
	while (sup->farm[++i])
	{
	/* 	write(1, "zdorov2!\n", 9);
	ft_putstr(sup->farm[i]->name);
	ft_putchar('\n');
	ft_putnbr(sup->farm[i]->x_coor);
	ft_putchar('\n');
	ft_putnbr(sup->farm[i]->y_coor);
	ft_putchar('\n');
	write(1, "poka2\n", 6);
	ft_putchar('\n'); */
		if (!(ft_strcmp(sup->farm[i]->name, tmp[0])) || (sup->farm[i]->x_coor == ft_atoi(tmp[1]) && sup->farm[i]->y_coor == ft_atoi(tmp[2])))
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
	ft_putstr(str);//
		ft_putchar('\n');//
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

int	make_tube(char *str)
{
	return (1);
}

t_lem	*tree_make(t_support *sup)
{
	char	*str;
	int 	i;

	i = 0;
	get_next_line(0, &str);
		ft_putstr(str);//
		ft_putchar('\n');//
	if (command_valid(str) == 1)
			sup->ants = atoi(str);
	else 
		ft_alarm(str, NULL);
	if (str)
			ft_strdel(&str);
	while (get_next_line(0, &str))
	{
			ft_putstr(str);
			ft_putchar('\n');
		if (command_valid(str) == 2)
			sup->farm[i++] = make_room(str, sup);
		else if (command_valid(str) == 3)
			sup->farm[i++] = make_important_room(str, 1, sup);
		else if (command_valid(str) == 4)
			sup->farm[i++] = make_important_room(str, 2, sup);
		else if (command_valid(str) == 5)
		{
			make_tube(str);
			if (str)
				ft_strdel(&str);
			break;
		}
		else 
			ft_alarm(str, NULL);
		if (str)
			ft_strdel(&str);
	}
	if (sup->start_mark != 1 || sup->end_mark != 1)
		ft_alarm(str, NULL);
	while (get_next_line(0, &str))	
	{
		ft_putstr(str);//
		ft_putchar('\n');//
		if (command_valid(str) == 5)
			make_tube(str);
		else
			ft_alarm(str, NULL);
		if (str)
			ft_strdel(&str);
	}
	return(NULL);
}

int		main(void)
{
	t_lem		*start;
	t_support	*sup;

	sup = support_struct_init();
	start = tree_make(sup);

	return(0);
}
