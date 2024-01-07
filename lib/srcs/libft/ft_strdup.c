/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:40:14 by habu-zua          #+#    #+#             */
/*   Updated: 2023/10/15 12:08:46 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str1)
{
	char	*str2;

	str2 = (char *)malloc(ft_strlen(str1) + 1);
	if (!str2)
		return (0);
	ft_memcpy(str2, str1, ft_strlen(str1) + 1);
	return (str2);
}
