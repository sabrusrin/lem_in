/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:48:39 by chermist          #+#    #+#             */
/*   Updated: 2019/10/22 17:13:30 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	rooms_valid_block(t_support *sup)
{
	char	*str;
	t_lem	*room;
	int		val;

	while (get_next_line(0, &str) && (val = command_valid(str, sup)))
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
	if (command_valid(str, sup) == 1)
		sup->ants = atoi(str);
	else
		ft_alarm(NULL, sup);
	rooms_valid_block(sup);
	while (get_next_line(0, &str))
	{
		ft_vpush_back(sup->in, &str, sizeof(char*));
		val = command_valid(str, sup);
		if (val == 6)
			;
		else if (val == 5)
			make_tube(str, sup);
		else
			ft_alarm(NULL, sup);
	}
	return (NULL);
}
/* 
void	options(char *av, t_opt *opt)
{
	if (!ft_strcmp("--help", av[1]))
	{
		ft_putstr("usage: ./lem-in [option] < graph\n");
		ft_putstr("options:\n\t--help : to read the manual\n");
		ft_putstr("\t--visu : to start with visualizer\n");
		ft_putstr("\t--paths : to print paths discovered\n");
		ft_putstr("\t--nomap : to print instructions only\n");
		return (0);
	}
	else if (!ft_strcmp("--visu", av[1]))
		opt->visu = 1;
	else if (!ft_strcmp("--paths", av[1]))
		opt->nomap = 1;
	else if (!ft_strcmp("--nomap", av[1]))
		opt->nomap = 1;
} */

int		main(int ac, char **av)
{
	t_lem		*start;
	t_support	*sup;
	t_lem		*tmp;
	//t_visu		visu;
	t_opt		opt;
	
//	if (ac > 1)
//	options(av[1], &opt);

	sup = support_struct_init();
	sup->opt = opt;
	start = tree_make(sup);
	//if (opt.visu)
//		visu_init(sup, &visu);
	path_find(sup);
	
	del_farm(sup);
	return (0);
}
