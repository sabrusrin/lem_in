/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 19:39:19 by ahugh             #+#    #+#             */
/*   Updated: 2019/09/11 23:34:59 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void				free_vector(const int fd, t_vector **v_arr)
{
	ft_memdel((void**)&v_arr[fd]->con);
	ft_memdel((void**)&v_arr[fd]);
	v_arr[fd] = NULL;
}

t_vector			*get_vector(const int fd, t_vector **v_arr)
{
	if (!v_arr || fd > STACK_SIZE || read(fd, 0, 0) == -1)
		return (NULL);
	if (!v_arr[fd] && (v_arr[fd] = (t_vector*)malloc(sizeof(t_vector))))
	{
		if ((v_arr[fd]->con = malloc(BUFF_SIZE)))
		{
			v_arr[fd]->fd = fd;
			v_arr[fd]->st = 0;
			v_arr[fd]->hd = 0;
			v_arr[fd]->sz = BUFF_SIZE;
		}
		else
		{
			ft_memdel((void**)&v_arr[fd]);
			v_arr[fd] = NULL;
		}
	}
	return (v_arr[fd]);
}

int					get_content_line(t_vector *v, char **line)
{
	if (v && line && v->hd && v->con)
	{
		while (v->con[v->st] != 10 && v->st < v->hd)
			v->st++;
		if (v->con[v->st] == 10)
		{
			if (!(*line = malloc(v->st + 1)))
				return (-1);
			ft_memcpy(*line, v->con, v->st);
			(*line)[v->st] = 0;
			v->st == v->sz ? v->st : v->st++;
			ft_memmove(v->con, &v->con[v->st], v->hd);
			if (!(v->st < v->hd ? (v->hd -= v->st) : 0))
				v->hd = 0;
			v->st = 0;
			return (1);
		}
	}
	return (0);
}

int					add_nl(t_vector *v)
{
	unsigned char	buff[BUFF_SIZE + 1];
	ssize_t			sz_rd;
	ssize_t			i;
	char			tr;

	i = 0;
	tr = 1;
	sz_rd = -1;
	while (v && ((sz_rd = read(v->fd, buff, BUFF_SIZE)) > 0))
	{
		if (v->sz - v->hd < BUFF_SIZE && (v->sz == 0 ? (v->sz = BUFF_SIZE) : 1))
			if ((v->con = ft_realloc(v->con, v->hd, (v->sz *= 2))) == NULL)
				break ;
		while (i < sz_rd)
		{
			if (tr && (buff[i] == 10) && tr--)
				v->st = v->hd;
			v->con[v->hd++] = buff[i++];
		}
		if (i != BUFF_SIZE)
			v->con[v->hd] = 10;
		if (!(i = 0) && v->con[v->st] == 10)
			return (1);
	}
	return (sz_rd == 0 ? 0 : -1);
}

int					get_next_line(const int fd, char **line)
{
	static t_vector	*v_arr[STACK_SIZE];
	t_vector		*v;
	int				nl;
	int				gcl;

	nl = 0;
	gcl = -1;
	v = NULL;
	if (fd > -1 && line && BUFF_SIZE > -1 && (v = get_vector(fd, v_arr)))
		if ((gcl = get_content_line(v, line)) == 0)
		{
			if ((nl = add_nl(v)) == 0)
				v->hd != 0 ? (v->con[v->hd] = 10) : 1;
			gcl = get_content_line(v, line);
		}
	if (gcl == 1)
		return (1);
	if (v)
		free_vector(fd, v_arr);
	if (gcl == 0)
	{
		(line != NULL) ? (line = NULL) : line;
		return (0);
	}
	return (-1);
}
