
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:49:13 by chermist          #+#    #+#             */
/*   Updated: 2019/09/08 19:43:11 by lkarlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

# include "libft.h"

# define WHITE 0
# define GRAY 1
# define BLACK 2

typedef struct	s_path
{
	int			flow;
	int			num;
	t_vec		*paths;
}				t_path;

typedef struct	s_lem
{
	char		*name;
	int			x_coor;
	int			y_coor;
	int			mark;
	int			val;
	int			ants;
	int			status;
	t_vec		*tubes;
	t_vec		*forks;
}				t_lem;

typedef struct	s_opt
{
	int			visu;
	int			paths;
	int			nomap;
}				t_opt;

typedef struct	s_support
{
	int			ants;
	int			start_mark;
	int			end_mark;
	char		**valid_arr;
	t_opt		opt;
	t_vec		*farm;
	t_vec		*in;
}				t_support;

void			ft_alarm (char **valid_arr, t_support *sup);
t_support		*support_struct_init(void);
void			del_farm(t_support *sup);
void			del_valid_arr(char **valid_arr);

int				command_valid(char *str, t_support *sup);
t_lem			*make_room(char *str, t_support *sup);
t_lem			*make_important_room(int status, t_support *sup);
void			tube_connect(t_lem *start, t_lem *end);
int				make_tube(char *str, t_support *sup);

t_lem			*tree_make(t_support *sup);
void			path_find(t_support *sup);

void			deal_conflict(t_support *sup, t_vec *paths);

void			print_path(t_vec *path);

#endif
