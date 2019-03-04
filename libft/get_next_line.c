/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 19:44:57 by squiquem          #+#    #+#             */
/*   Updated: 2017/12/05 23:34:19 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		cmp_fd(t_gnl *a, int *b)
{
	return (a->fd - *b);
}

static void		free_gnl(void *a, size_t size)
{
	(void)size;
	ft_strdel(&((t_gnl *)a)->str);
	free(a);
}

static t_list	*newfd(t_list **head, int fd)
{
	t_gnl		new;

	new.fd = fd;
	new.str = ft_memalloc((BUFF_SIZE > 0 ? BUFF_SIZE : 0) + 1);
	ft_lstadd(head, ft_lstnew(&new, sizeof(t_gnl)));
	return (*head);
}

static int		read_loop(int fd, char **line, char *gnl)
{
	char	buf[BUFF_SIZE + 1];
	char	*pos;
	char	*tmp;
	int		ret;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = *line;
		if ((pos = ft_strchr(buf, '\n')))
		{
			ft_strcpy(gnl, pos + 1);
			*pos = 0;
		}
		if (!(*line = ft_strjoin(*line, buf)))
			return (-1);
		ft_strdel(&tmp);
		if (pos)
			return (1);
	}
	if (ret < 0)
		return (-1);
	return (**line ? 1 : 0);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*tmp;
	char			*pos;
	char			*gnl;
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	if (!(tmp = ft_lstfind(head, (void *)&fd, &cmp_fd)))
		tmp = newfd(&head, fd);
	gnl = ((t_gnl *)tmp->content)->str;
	if (!(*line = ft_strdup(gnl)))
		return (-1);
	ft_bzero(gnl, BUFF_SIZE + 1);
	if ((pos = ft_strchr(*line, '\n')))
	{
		ft_strcpy(gnl, pos + 1);
		*pos = 0;
		return (1);
	}
	if (!(ret = read_loop(fd, line, gnl)))
		ft_lstdelif(&head, (int *)&fd, cmp_fd, &free_gnl);
	return (ret);
}
