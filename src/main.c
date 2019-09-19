/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:39 by chermist          #+#    #+#             */
/*   Updated: 2019/09/19 08:23:54 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	rooms_valid_block(t_support *sup)
{
	char	*str;
	t_lem	*room;
	int		val;

	while (get_next_line(0, &str) && (val = command_valid(str, sup)))
	{
		if (val == 6)
			;
		else if (val == 2 && (room = make_room(str, sup)))
			ft_vpush_back(sup->farm, &room, sizeof(t_lem*));
		else if (val == 3 && (room = make_important_room(1, sup)))
			ft_vpush_back(sup->farm, &room, sizeof(t_lem*));
		else if (val == 4 && (room = make_important_room(2, sup)))
			ft_vpush_back(sup->farm, &room, sizeof(t_lem*));
		else if (val == 5)
		{
			if (sup->start_mark != 1 || sup->end_mark != 1)
				ft_alarm(str, NULL, sup);
			make_tube(str, sup);
		}
		else
			ft_alarm(str, NULL, sup);
		ft_strdel(&str);
	}
}

t_lem	*tree_make(t_support *sup)
{
	char	*str;
	int		i;
	int		val;

	i = 0;
	get_next_line(0, &str);
	if (command_valid(str, sup) == 1)
		sup->ants = atoi(str);
	else
		ft_alarm(str, NULL, sup);
	ft_strdel(&str);
	rooms_valid_block(sup);
	while (get_next_line(0, &str))
	{
		val = command_valid(str, sup);
		if (val == 6)
			;
		else if (val == 5)
			make_tube(str, sup);
		else
			ft_alarm(str, NULL, sup);
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
	start = tree_make(sup);
	path_find(sup);
	ft_putchar('\n');
	while (sup->farm->size > ++i && (i2 = -1))
	{
		tmp = *(t_lem**)ft_vat(sup->farm, i);
		while (tmp->tubes->size > ++i2)
		{
			printf("|%s-%s\n", tmp->name,
					(*(t_lem**)ft_vat(tmp->tubes, i2))->name);
		}
	}
	del_farm(sup);
	return (0);
}
