/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:25:23 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/27 11:17:04 by habu-zua         ###   ########.fr       */
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

void	handle_echo(t_parse *data)
{
	printf("handle_echo\n");
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 1;
	while (data->cmds[0][i] && is_n_flag(data->cmds[0][i]))
	{
		n_flag = 0;
		i++;
	}
	while (data->cmds[0][i])
	{
		write(1, data->cmds[0][i], ft_strlen(data->cmds[0][i]));
		if (data->cmds[0][i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n_flag)
		write(1, "\n", 1);
	
}
