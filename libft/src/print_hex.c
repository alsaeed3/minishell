/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:37:25 by alsaeed           #+#    #+#             */
/*   Updated: 2023/07/24 15:52:10 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	print_hex(unsigned int n, char c)
{
	int		len;
	char	*s;

	len = 0;
	if (c == 'x')
		s = "0123456789abcdef";
	if (c == 'X')
		s = "0123456789ABCDEF";
	if (n > 15)
		len += print_hex(n / 16, c);
	len += ft_putchar(s[n % 16]);
	return (len);
}
