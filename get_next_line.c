/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaetern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 02:58:20 by ksaetern          #+#    #+#             */
/*   Updated: 2017/03/24 02:58:24 by ksaetern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

static t_list		*find_fd(t_list **saved, int fd)
{
	t_list			*node;
	t_next			*dealio;

	node = *saved;
	while (node)
	{
		if (((t_next*)node->content)->fd == fd)
			return (node);
		node = node->next;
	}
	if (!node)
	{
		dealio = (t_next*)ft_memalloc(sizeof(t_next));
		dealio->str = "\0";
		dealio->fd = fd;
		node = ft_lstnew(dealio, sizeof(t_next));
		ft_lstadd(saved, node);
		node = *saved;
	}
	return (node);
}

int					parse_saved(t_list *list, char **line, int nline)
{
	char			*tmp;
	int				nlen;

	nlen = ft_strlen(((t_next*)list->content)->str);
	tmp = ((t_next*)list->content)->str;
	if (ft_strchr(((t_next*)list->content)->str, '\n'))
	{
		*line = ft_strsub(((t_next*)list->content)->str, 0, nline);
		((t_next*)list->content)->str =
		ft_strsub(((t_next*)list->content)->str, (nline + 1),
			((nlen - nline) + 1));
		free(tmp);
		return (1);
	}
	if (ft_strlen(((t_next *)list->content)->str) > 0)
	{
		*line = ft_strdup(((t_next *)list->content)->str);
		ft_strclr(((t_next *)list->content)->str);
		free(tmp);
		return (1);
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*saved;
	t_list			*list;
	char			str[BUFF_SIZE + 1];
	int				get;
	int				nline;

	if (fd < 0 || read(fd, str, 0) < 0 || !line)
		return (-1);
	list = find_fd(&saved, fd);
	while ((get = read(fd, str, BUFF_SIZE)) > 0)
	{
		str[get] = '\0';
		((t_next*)list->content)->str =
		ft_strjoin(((t_next*)list->content)->str, str);
		if (ft_strchr(str, '\n'))
			break ;
	}
	nline = ft_until(((t_next*)list->content)->str, '\n');
	if (parse_saved(list, line, nline))
		return (1);
	return (0);
}
