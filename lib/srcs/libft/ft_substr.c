/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:26:23 by habu-zua          #+#    #+#             */
/*   Updated: 2023/10/15 17:46:31 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	sublen;

	if (s == NULL)
		return (NULL);
	sublen = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	while (sublen < len && s[sublen + start])
		sublen++;
	new_str = (char *)malloc(sizeof(char) * (sublen + 1));
	if (new_str != NULL)
	{
		new_str[sublen] = '\0';
		ft_strlcpy(new_str, s + start, sublen + 1);
	}
	return (new_str);
}
