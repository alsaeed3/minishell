/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:25:23 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/14 20:55:43 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static int	is_n_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

void	handle_echo(t_parse *data, int x)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 1;
	while (data->cmds[x][i] && is_n_flag(data->cmds[x][i]))
	{
		n_flag = 0;
		i++;
	}
	while (data->cmds[x][i])
	{
		write(1, data->cmds[x][i], ft_strlen(data->cmds[x][i]));
		if (data->cmds[x][i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n_flag)
		write(1, "\n", 1);
}
