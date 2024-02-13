/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:33:05 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/13 19:44:42 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free_set_null(array[i]);
		i++;
	}
	free_set_null(array);
}

void	free_set_null(void *ptr)
{
	if (ptr != NULL)
	{
		free (ptr);
		ptr = NULL;
	}
}
