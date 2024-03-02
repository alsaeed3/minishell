/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:25:23 by habu-zua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/01 13:46:29 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/14 20:55:43 by alsaeed          ###   ########.fr       */
>>>>>>> main
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

<<<<<<< HEAD
void	handle_echo(t_parse *data)
=======
void	handle_echo(t_parse *data, int x)
>>>>>>> main
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 1;
<<<<<<< HEAD
	while (data->cmds[0][i] && is_n_flag(data->cmds[0][i]))
=======
	while (data->cmds[x][i] && is_n_flag(data->cmds[x][i]))
>>>>>>> main
	{
		n_flag = 0;
		i++;
	}
<<<<<<< HEAD
	while (data->cmds[0][i])
	{
		write(1, data->cmds[0][i], ft_strlen(data->cmds[0][i]));
		if (data->cmds[0][i + 1])
=======
	while (data->cmds[x][i])
	{
		write(1, data->cmds[x][i], ft_strlen(data->cmds[x][i]));
		if (data->cmds[x][i + 1])
>>>>>>> main
			write(1, " ", 1);
		i++;
	}
	if (n_flag)
		write(1, "\n", 1);
<<<<<<< HEAD
	
=======
>>>>>>> main
}
