/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:33:05 by alsaeed           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/13 19:44:42 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/15 16:23:01 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_free_array(char ***array)
{
	int	i;

	if (!*array)
		return ;
	i = 0;
	while ((*array)[i])
	{
<<<<<<< HEAD
		free_set_null(array[i]);
		i++;
	}
	free_set_null(array);
=======
		free_set_null((void **)&(*array)[i]);
		i++;
	}
	free_set_null((void **)array);
>>>>>>> main
}

void	free_set_null(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
