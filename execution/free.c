/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:26:04 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/07 17:23:24 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	free_exit(t_parse *data, int status)
{
	free_env(data->env);
	free_set_null(data->pwd);
	rl_clear_history();
	exit(status);
}

void	free_close_fd(t_parse *data, int oldfd[2], int mode, int status)
{
	free_parser(&data);
	free_set_null(data->pwd);
	ft_free_array(data->env);
	free_set_null(data);
	if (mode == 1)
	{
		close(oldfd[0]);
		close(oldfd[1]);
	}
	rl_clear_history();
	exit(status);
}

void	print_message(char *cmd, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(message, 2);
}

void	dup2_close(int oldfd[2])
{
	dup2(oldfd[0], 0);
	dup2(oldfd[1], 1);
	close(oldfd[0]);
	close(oldfd[1]);
}
