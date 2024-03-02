/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:24:03 by alsaeed           #+#    #+#             */
/*   Updated: 2023/10/12 16:24:28 by alsaeed          ###   ########.fr       */
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:24:03 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/15 16:21:37 by alsaeed          ###   ########.fr       */
>>>>>>> main
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
<<<<<<< HEAD
	free (str);
	str = NULL;
	if (ft_array_size(array) <= 1)
	{
		ft_free_array(array);
=======
	free_set_null((void **)&str);
	if (ft_array_size(array) <= 1)
	{
		ft_free_array(&array);
>>>>>>> main
		exit (0);
	}
	return (array);
}
