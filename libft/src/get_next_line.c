/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:35:56 by alsaeed           #+#    #+#             */
/*   Updated: 2023/09/01 17:11:35 by alsaeed          ###   ########.fr       */
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:35:56 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/15 14:09:24 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	*free_strjoin(char *s1, char *s2)
{
	char	*joint;

	joint = ft_strjoin(s1, s2);
	if (s1)
<<<<<<< HEAD
		free(s1);
=======
		free_set_null((void **)&s1);
>>>>>>> main
	return (joint);
}

static char	*ft_read(int fd, char *stash)
{
	char	*buf;
	ssize_t	read_bytes;

	if (!stash)
	{
		stash = malloc(sizeof(char));
		*stash = '\0';
	}
	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
<<<<<<< HEAD
			return (free(buf), NULL);
=======
			return (free_set_null((void **)&buf), NULL);
>>>>>>> main
		buf[read_bytes] = '\0';
		stash = free_strjoin(stash, buf);
		if (ft_strchr(stash, '\n'))
			break ;
	}
<<<<<<< HEAD
	free(buf);
=======
	free_set_null((void **)&buf);
>>>>>>> main
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX
		|| read(fd, NULL, 0))
		return (NULL);
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	line = ret_line(stash);
	stash = update_stash(stash);
	return (line);
}
