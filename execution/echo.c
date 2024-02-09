/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:25:23 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/09 18:00:27 by habu-zua         ###   ########.fr       */
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
	int j;
	int len;
	char *ret;

	len = ft_strlen(str);
	i = -1;
	j = 0;
	while (++i < len)
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			
			else if (str[i + 1] == '0')
				ft_putstr_fd("minishell", 1);
			else if ((str[i + 1] >= 'a' && str[i + 1] <= 'z') \
			|| (str[i + 1] >= 'A' && str[i + 1] <= 'Z'))
				return ;
			i++;
			continue;
		}
		else
			(str[i], 1);
	}
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
		// if (check_dol_ques(data->cmds[x][i]))
		// 	print_dol_ques(data->cmds[x][i], data);
		write(1, data->cmds[x][i], ft_strlen(data->cmds[x][i]));
		if (data->cmds[x][i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n_flag)
		write(1, "\n", 1);
}
