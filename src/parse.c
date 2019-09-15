/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:47 by chermist          #+#    #+#             */
/*   Updated: 2019/09/15 22:45:31 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		command_valid(char *str)
{
	char	**tmp;
	int		i;
	int		arr;

	i = 0;
	arr = 0;
	if (str[0] == '#' && str[1] != '#')
		return(6);
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
		if (!(ft_strcmp((*(t_lem**)ft_vat(sup->farm, i))->name, tmp[0])) && ++connect)
			start = *(t_lem**)ft_vat(sup->farm, i);
		if (!(ft_strcmp((*(t_lem**)ft_vat(sup->farm, i))->name, tmp[1])) && ++connect)
			end = *(t_lem**)ft_vat(sup->farm, i);
	}
	if ((i = -1) && connect != 2)
		ft_alarm(str, tmp);  //уничтожить все гавно? Или природа сама разберется? (sup->farm)
	ft_vpush_back(start->tubes, &end, sizeof(t_lem*));
	del_valid_arr(tmp);
	return (1);
}

void	rooms_valid_block(char *str, t_support *sup)
{
	int i;
	t_lem *room;
	void  *el;

	i = 0;
	while (get_next_line(0, &str))
	{
		if (command_valid(str) == 6)
		{
			if (str)
				ft_strdel(&str);
			continue;
		}
		if (command_valid(str) == 2)
		{
			room = make_room(str, sup);
			ft_vpush_back(sup->farm, &room, sizeof(t_lem*));
		}
		else if (command_valid(str) == 3)
		{
			room = make_important_room(str, 1, sup);
			ft_vpush_back(sup->farm, &room, sizeof(t_lem*));
		}
		else if (command_valid(str) == 4)
		{
			room = make_important_room(str, 2, sup);
			ft_vpush_back(sup->farm, &room, sizeof(t_lem*));
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
	while (get_next_line(0, &str))
	{
		if (command_valid(str) == 6)
		{
			if (str)
				ft_strdel(&str);
			continue;
		}
		if (command_valid(str) == 5)
			make_tube(str, sup);
		else
			ft_alarm(str, NULL);
		if (str)
			ft_strdel(&str);
	}
	return (NULL);
}
