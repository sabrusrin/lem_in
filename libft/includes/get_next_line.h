/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:17:37 by lkarlon-          #+#    #+#             */
/*   Updated: 2019/11/03 18:17:42 by lkarlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1
# define STACK_SIZE 8192
# include "libft.h"

int					get_next_line(const int fd, char **line);

typedef struct		s_vector
{
	char			*con;
	size_t			fd;
	size_t			st;
	size_t			hd;
	size_t			sz;
}					t_vector;

#endif
