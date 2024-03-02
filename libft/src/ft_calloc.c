/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:35:04 by alsaeed           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/24 14:30:25 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/07 14:38:56 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

<<<<<<< HEAD
	if (count > (SIZE_MAX / size)/*  || !size || !count */)
=======
	if (count > (SIZE_MAX / size) || !size || !count)
>>>>>>> main
		return (NULL);
	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
