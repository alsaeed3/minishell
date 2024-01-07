/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:35:13 by habu-zua          #+#    #+#             */
/*   Updated: 2023/08/14 13:50:03 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*dst;

	if (count != 0 && size != 0 && (count > INT_MAX / size))
		return (NULL);
	total_size = size * count;
	dst = malloc(total_size);
	if (!dst)
		return (0);
	ft_bzero(dst, total_size);
	return (dst);
}
