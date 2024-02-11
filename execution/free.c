/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:26:04 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/11 14:29:12 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	free_exit(t_parse *data, int status)
{
	free_data(&data);
	free_env(data->env);
	free_set_null(data->pwd);
	free_set_null(data);
	// rl_clear_history();
	ft_putendl_fd("exit", 1);
	exit(status);
}

void	free_close_fd(t_parse *data, int mode, int status)
{
	free_data(&data);
	free_set_null(data->pwd);
	ft_free_array(data->env);
	free_set_null(data);
	if (mode == 1)
	{
		if(data->fds)
		{
			close(data->fds->oldfd[0]);
			close(data->fds->oldfd[1]);
			close(data->fds->pfd[0]);
			close(data->fds->pfd[1]);
		}
	}
	// rl_clear_history();
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
	if (dup2(oldfd[0], 0) == -1)
		ft_putendl_fd("dup2 failed", 2);
	close(oldfd[0]);
	if (dup2(oldfd[1], 1) == -1)
		ft_putendl_fd("dup2 failed", 2);
	close(oldfd[1]);
}
