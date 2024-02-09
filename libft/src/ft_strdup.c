/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:35:24 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/02 20:27:07 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(char *s1)
{
	char	*dup;
	int		count;

	count = 0;
	dup = NULL;
	if (!s1)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dup)
		return (NULL);
	while (*s1)
	{
		*dup++ = *s1++;
		count++;
	}
	*dup = '\0';
	dup = dup - count;
	s1 = s1 - count;
	return (dup);
}
