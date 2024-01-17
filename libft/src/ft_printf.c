/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:11:31 by alsaeed           #+#    #+#             */
/*   Updated: 2023/09/01 16:48:27 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_check(char c, va_list lst)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_putchar(va_arg(lst, int));
	else if (c == 's')
		len += ft_putstr(va_arg(lst, char *));
	else if (c == 'd' || c == 'i')
		len += ft_putnbr(va_arg(lst, int));
	else if (c == 'p')
		len += print_pointer(va_arg(lst, unsigned long));
	else if (c == 'x' || c == 'X')
		len += print_hex(va_arg(lst, unsigned int), c);
	else if (c == 'u')
		len += print_undec(va_arg(lst, unsigned int));
	else if (c == '%')
		len += ft_putchar(c);
	return (len);
}

int	ft_printf(char *str, ...)
{
	va_list	lst;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!str)
	{
		write(1, "(null)\n", 8);
		return (0);
	}
	va_start(lst, str);
	while (str[i])
	{
		if (str[i] == '%')
			len += ft_check(str[++i], lst);
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end (lst);
	return (len);
}
