/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:24:03 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/06 21:00:19 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	**ft_get_array(int ac, char **av)
{
	char	*str;
	char	**array;

	str = NULL;
	array = NULL;
	str = ft_strjoin_sp(ac, av);
	array = ft_split(str, ' ');
	free_set_null(str);
	if (ft_array_size(array) <= 1)
	{
		ft_free_array(array);
		exit (0);
	}
	return (array);
}
