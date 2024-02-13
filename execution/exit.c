/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:57:59 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/11 18:41:34 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

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
	}
	return (1);
}

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
}
