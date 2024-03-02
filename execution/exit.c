/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:57:59 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/08 21:14:41 by habu-zua         ###   ########.fr       */
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:57:59 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/21 16:58:56 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

<<<<<<< HEAD
int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
=======
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
>>>>>>> main
	}
	return (1);
}

<<<<<<< HEAD
void	handle_exit(char **args, t_parse *data)
{
	int	status;

	status = 0;
	if (args[1])
	{
		if (is_number(args[1]))
		{
			if (args[2])
			{
				ft_error("\tminishell: too many argument");
				data->exit_status = 2;
				return ;
			}
			status = ft_atoi(args[1], NULL);
			if (status > 255 || status < 0)
				status = 255;
		}
		else
		{
			ft_error("\t\tminishell: numeric argument is required");
			data->exit_status = 2;
		}
	}
	free_exit(data, status);
=======
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

void	handle_exit(char **args, t_parse *data, t_pipe *pipes, int mode)
{
	long long	status;
	int			over_under_flow;

	if (mode == 1 && pipes)
	{
		free_set_null((void **)&pipes->pipe_fds);
		free_set_null((void **)&pipes->pid);
	}
	if (args[1])
	{
		if (!is_numeric(args[1]))
			free_exit(data, 255, 1);
		else if (args[2])
			free_exit(data, 1, 2);
		else
		{
			status = ft_atoll(args[1], &over_under_flow);
			if (over_under_flow)
				free_exit(data, 255, 1);
			free_exit(data, status, 0);
		}
	}
	free_exit(data, 0, 0);
>>>>>>> main
}
