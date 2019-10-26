/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:39 by chermist          #+#    #+#             */
/*   Updated: 2019/10/26 03:37:30 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	compare_coords(t_support *sup, int x, int y)
{
	if (!sup->farm->size)
	{
		sup->xy[0][0] = x;
		sup->xy[0][1] = y;
	}
	if (x < sup->xy[0][0])
		sup->xy[0][0] = x;
	if (y < sup->xy[0][1])
		sup->xy[0][1] = y;
	if (!sup->xy[1][0] || x > sup->xy[1][0])
		sup->xy[1][0] = x;
	if (!sup->xy[1][1] || y > sup->xy[1][1])
		sup->xy[1][1] = y;
}

void	rooms_valid_block(t_support *sup)
{
	char	*str;
	t_lem	*room;
	int		val;

	while (get_next_line(0, &str) && (val = command_valid(str, sup, 0, 0)))
	{
		ft_vpush_back(sup->in, &str, sizeof(char*));
		if (val == 2 && (room = make_room(str, sup)))
			ft_vpush_back(sup->farm, &room, sizeof(t_lem*));
		else if (val == 3 && (room = make_important_room(1, sup)))
			ft_vpush_back(sup->farm, &room, sizeof(t_lem*));
		else if (val == 4 && (room = make_important_room(2, sup)))
			ft_vpush_back(sup->farm, &room, sizeof(t_lem*));
		else if (val == 5)
		{
			if (sup->start_mark != 1 || sup->end_mark != 1)
				ft_alarm(NULL, sup);
			make_tube(str, sup);
		}
		else if (val != 6)
			ft_alarm(NULL, sup);
	}
}

t_lem	*tree_make(t_support *sup)
{
	char	*str;
	int		val;

	get_next_line(0, &str);
	ft_vpush_back(sup->in, &str, sizeof(char*));
	if (command_valid(str, sup, 0, 0) == 1)
		sup->ants = atoi(str);
	else
		ft_alarm(NULL, sup);
	rooms_valid_block(sup);
	while (get_next_line(0, &str))
	{
		ft_vpush_back(sup->in, &str, sizeof(char*));
		val = command_valid(str, sup, 0, 0);
		if (val == 6)
			;
		else if (val == 5)
			make_tube(str, sup);
		else
			ft_alarm(NULL, sup);
	}
	return (NULL);
}

int		options(t_support *sup, char *av, t_opt *opt)
{
	opt->visu = 0;
	opt->nomap = 0;
	opt->paths = 0;
	if (!ft_strcmp("--help", av))
	{
		ft_putstr("usage: ./lem-in --[option] < graph\n");
		ft_putstr("options:\n\t--help : to read the manual\n");
		ft_putstr("\tv : to start with visualizer\n");
		ft_putstr("\tn : to print instructions only\n");
		return (1);
	}
	else
	{
		if (ft_strchr(av, 'v'))
		{
			opt->visu = 1;
			sup->lines = ft_vnew(200, sizeof(t_lines*));
		}
		if (!ft_strchr(av, 'p'))
			opt->paths = 1;
		if (ft_strchr(av, 'n'))
			opt->nomap = 1;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_lem		*start;
	t_support	sup;
	t_lem		*tmp;
	t_visu		visu;
	t_opt		opt;

	if (ac > 1)
		if (options(&sup, av[1], &opt))
			return (0);
	if (ac == 3)
		visu.d = ft_atoi(av[2]);
	else
		visu.d = 1200;
	support_struct_init(&sup);
	sup.opt = opt;
	sup.cons = 0;
	start = tree_make(&sup);
	if (opt.visu)
		visu_init(&sup, &visu);
	path_find(&sup);
	if (opt.visu)
		visu_move(&sup, &visu);
	del_farm(&sup);
	return (0);
}
