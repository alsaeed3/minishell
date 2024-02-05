/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:23:16 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/05 21:10:56 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlen(char *str)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count])
		count++;
	str = str - count;
	return (count);
}
