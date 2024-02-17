/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:57:59 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/17 19:47:10 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

int	is_numeric(const char *str)
{
	if (*str && (*str == '+' || *str == '-'))
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
static int	check_overflow(long long num, int sign, int digit)
{
	if (num > LONG_MAX / 10 || (num == LONG_MAX / 10 && digit > LLONG_MAX % 10))
	{
		if (sign == 1 || (sign == -1 && (digit > 8)))
			return (1);
	}
	return (0);
}

long long	ft_atoll(const char *str, int *over_under_flow)
{
	int			i;
	int			sign;
	long long	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (check_overflow(num, sign, str[i] - '0'))
			return (*over_under_flow = 1, 0);
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (*over_under_flow = 0, num * sign);
}

void handle_non_numeric_arg(t_parse *data)
{
	ft_putendl_fd("exit", 1);
	ft_putendl_fd("minishell: exit: numeric argument required", 2);
	free_exit(data, 2);
}

static void	handle_too_many_args(t_parse *data)
{
	ft_putendl_fd("exit", 1);
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	free_exit(data, 1);
}

void	handle_exit(char **args, t_parse *data)
{
	long long	status;
	int			over_under_flow;
	
	if (args[1])
	{
		if (!is_numeric(args[1]))
				handle_non_numeric_arg(data);
		else if(args[2])
				handle_too_many_args(data);
		else
		{
			status = ft_atoll(args[1], &over_under_flow);
			if (over_under_flow)
			{
				ft_putendl_fd("exit", 1);
				ft_putendl_fd("minishell: exit: numeric argument required", 2);
				free_exit(data, 255);
			}
			ft_putendl_fd("exit", 1);
			free_exit(data, status);
		}
	}
	ft_putendl_fd("exit", 1);
	free_exit(data, 0);
}
