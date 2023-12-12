/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:09:01 by alsaeed           #+#    #+#             */
/*   Updated: 2023/09/01 17:12:32 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlen(char *buf)
{
	size_t	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlen_nl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!s1 || !s2)
		return (NULL);
	join = malloc(sizeof(char) * len);
	if (!join)
		return (NULL);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

char	*ret_line(char *stash)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!stash || !stash[i])
		return (NULL);
	i = ft_strlen_nl(stash) + 2;
	ret = (char *)malloc(sizeof(char) * i);
	if (!ret)
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
	{
		ret[i] = stash[i];
		i++;
	}
	if (stash[i] == '\0' || stash[i] == '\n')
	{
		ret[i] = stash[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*update_stash(char *stash)
{
	char	*update;
	size_t	i;
	size_t	j;

	i = 0;
	if (!stash)
		return (NULL);
	i = ft_strlen_nl(stash);
	update = NULL;
	if (i < ft_strlen(stash))
		update = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!update)
		return (free(stash), NULL);
	i++;
	j = 0;
	while (stash[i])
	{
		update[j] = stash[i];
		j++;
		i++;
	}
	update[j] = '\0';
	if (update[0] == '\0')
		return (free(update), free(stash), NULL);
	return (free(stash), update);
}
