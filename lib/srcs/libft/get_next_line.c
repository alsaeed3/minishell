/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:27:24 by habu-zua          #+#    #+#             */
/*   Updated: 2023/10/22 11:00:28 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static t_gnl	*gnl_new(int fd)
{
	t_gnl	*result;

	result = malloc(sizeof(t_gnl));
	if (result == NULL)
		return (0);
	result->fd = fd;
	result->line = 0;
	result->next = 0;
	return (result);
}

static t_gnl	*check_gnl(t_gnl **store, int fd)
{
	t_gnl	*ptr;

	if (!(*store))
		return ((*store) = gnl_new(fd));
	ptr = *store;
	while (ptr->next && ptr->fd != fd)
		ptr = ptr->next;
	if (ptr->fd == fd)
		return (ptr);
	return ((ptr->next) = gnl_new(fd));
}

static void	gnl_del(t_gnl **store, int fd)
{
	t_gnl	*prev;
	t_gnl	*curr;

	if (!((*store)->next))
	{
		free(*store);
		*store = 0;
		return ;
	}
	prev = 0;
	curr = *store;
	while (curr->next && curr->fd != fd)
	{
		prev = curr;
		curr = prev->next;
	}
	if (prev && curr->next)
		prev->next = curr->next;
	else if (!prev && curr->next)
		*store = curr->next;
	else
		prev->next = 0;
	free(curr);
}

static int	ft_check_line(t_gnl **store, t_gnl *gnl, char **line)
{
	char	*ptr;
	char	*tmp;

	ptr = ft_strchr(gnl->line, '\n');
	if (ptr)
	{
		*line = ft_strndup(gnl->line, ptr - gnl->line);
		tmp = ft_strndup(ptr + 1, ft_strlen(ptr + 1));
		free(gnl->line);
		gnl->line = tmp;
		return (1);
	}
	else
	{
		*line = gnl->line;
		gnl_del(store, gnl->fd);
		return (0);
	}
}

int	get_next_line(int fd, char **line)
{
	static t_gnl	*store;
	long			read_size;
	t_gnl			*ptr;
	char			buf[BUFFER_SIZE + 1];

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	ptr = check_gnl(&store, fd);
	if (ptr == NULL)
		return (-1);
	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size >= 0)
	{
		buf[read_size] = 0;
		if (ptr->line)
			ptr->line = ft_strjoin_free(ptr->line, buf, 1);
		else
			ptr->line = ft_strndup(buf, read_size);
		if (ft_strchr(ptr->line, '\n') || read_size == 0)
			break ;
		read_size = read(fd, buf, BUFFER_SIZE);
	}
	if (read_size < 0)
		return (-1);
	return (ft_check_line(&store, ptr, line));
}
