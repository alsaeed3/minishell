/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_undec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:11:44 by alsaeed           #+#    #+#             */
/*   Updated: 2023/07/24 15:52:19 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	print_undec(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
		len += print_undec(n / 10);
	len += ft_putchar((n % 10) + '0');
	return (len);
}
