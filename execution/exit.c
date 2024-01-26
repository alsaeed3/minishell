/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:57:59 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/26 18:52:31 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	error_sentence(char *str, int status)
{
	(void)status;
	ft_putstr_fd(str, 2);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	handle_exit(char **args, t_parse *data)
{
	int	status;
	int	error;

	status = 0;
	if (args[1])
	{
		if (is_number(args[1]))
		{
			if (args[2])
				return (error_sentence("\tminishell: too many argument\n", 2));
			status = ft_atoi(args[1], &error);
			if (status > 255)
				status = 255;
			else if (status < 0)
				status = 255;
		}
		else
			error_sentence("\t\tminishell: numeric argument is required\n", 2);
	}
	free_exit(data, status);
}
