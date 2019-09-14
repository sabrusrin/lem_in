
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

typedef struct	s_lem
{
    char            *name;
    int             x_coor;
    int             y_coor;
    int             mark;
    int             ants;
    int             room_status;
    struct s_lem    **tubes;
}				t_lem;

typedef struct	s_support
{
    int         ants;
    int         start_mark;
    int         end_mark; 
    char        **valid_arr;
	t_vec		*farm;
//    t_lem	    **farm;
}				t_support;

void        ft_alarm (char *str, char **valid_arr);
t_support   *support_struct_init(void);
void	    del_valid_arr(char **valid_arr);

#endif