/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:25:23 by habu-zua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/09 11:31:11 by alsaeed          ###   ########.fr       */
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
static t_bool	check_dol_ques(char *str)
{
	int	i;
	int len;

	len = ft_strlen(str);
	i = -1;
	while (++i < len)
	{
		if (str[i] == '$')
			return (TRUE);
	} 
	return (FALSE);
}

static void	print_dol_ques(char *str, t_parse *data)
{
	int	i;
	int len;

	len = ft_strlen(str);
	i = -1;
	while (++i < len)
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				ft_putnbr_fd(data->exit_status, 1);
			else if (str[i + 1] == '0')
				ft_putstr_fd("minishell", 1);
			else if ((str[i + 1] >= 'a' && str[i + 1] <= 'z') \
			|| (str[i + 1] >= 'A' && str[i + 1] <= 'Z'))
				return ;
			i++;
			continue;
		}
		else
			ft_putchar_fd(str[i], 1);
	}
}

=======
>>>>>>> main
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
<<<<<<< HEAD
		if (check_dol_ques(data->cmds[x][i]))
			print_dol_ques(data->cmds[x][i], data);
		else
			write(1, data->cmds[x][i], ft_strlen(data->cmds[x][i]));
=======
		write(1, data->cmds[x][i], ft_strlen(data->cmds[x][i]));
>>>>>>> main
		if (data->cmds[x][i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n_flag)
		write(1, "\n", 1);
}
