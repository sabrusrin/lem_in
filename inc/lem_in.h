/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:49:13 by chermist          #+#    #+#             */
/*   Updated: 2019/10/26 17:36:53 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

# include "libft.h"
# include "visu.h"

# define WHITE 0
# define GRAY 1
# define BLACK 2

typedef struct	s_path
{
	int			flow;
	int			pflow;
	int			num;
	t_vec		*paths;
}				t_path;

typedef struct	s_lem
{
	char		*name;
	int			x;
	int			y;
	int			mark;
	int			ants;
	int			status;
	t_vec		*tubes;
	t_vec		*forks;
}				t_lem;

typedef struct	s_lines
{
	t_lem		*a;
	t_lem		*b;
}				t_lines;

typedef struct	s_move
{
	float		a[2];
	int			b[2];
	float		delta[2];
	int			se[2];
}				t_move;

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
	int			cons;
	int			xy[2][2];
	char		**valid_arr;
	t_opt		opt;
	t_vec		*farm;
	t_vec		*lines;
	t_vec		*in;
	t_vec		*moves;
}				t_support;

void			ft_alarm (char **valid_arr, t_support *sup);
void			support_struct_init(t_support *sup);
void			del_farm(t_support *sup);
void			del_valid_arr(char **valid_arr);

int				command_valid(char *str, t_support *sup, int i, int a);
t_lem			*make_room(char *str, t_support *sup);
t_lem			*make_important_room(int status, t_support *sup);
void			tube_connect(t_lem *start, t_lem *end, t_support *sup);
int				make_tube(char *str, t_support *sup);
int				check_id(char *str, t_support *sup);
void			compare_coords(t_support *sup, int x, int y);
int				check_weight(t_vec *paths, t_vec *path, int j, int ants);

t_lem			*tree_make(t_support *sup);
void			path_find(t_support *sup);

void			lem_in(t_support *sup, t_vec *paths);

void			print_in(t_support *sup);
void			print_moves(t_vec *p, t_support *sup);
void			move_to_end(t_support *sup, t_vec *path);

SDL_Texture		*visu_text(t_visu *v, char *text, SDL_Rect *rect, int xy[]);
int				visu_init(t_support *sup, t_visu *v);
int				visu_move(t_support *sup, t_visu *v);
void			print_rooms(t_support *sup, t_visu *v);
void			print_lines(t_support *sup, t_visu *v);
void			visu_free(t_support *sup);
void			put_default(t_support *sup, t_visu *v, int s, int e);
void			print_se(t_visu *v, SDL_Texture *texture, SDL_Rect rect,
																int xy[]);

#endif
