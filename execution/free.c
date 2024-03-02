/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:26:04 by habu-zua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/09 10:46:37 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/21 17:00:19 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

<<<<<<< HEAD
void	free_exit(t_parse *data, int status)
{
	free_parser(&data);
	free_env(data->env);
	free_set_null(data->pwd);
	free_set_null(data);
	// rl_clear_history();
	// ft_putendl_fd("exit", 1);
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
	// rl_clear_history();
=======
void	free_exit(t_parse *data, int status, int mode)
{
	ft_putendl_fd("exit", 1);
	if (mode == 1)
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
	if (mode == 2)
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	if (data->fds)
	{
		if (data->fds->oldfd[0])
			close(data->fds->oldfd[0]);
		if (data->fds->oldfd[1])
			close(data->fds->oldfd[1]);
		free (data->fds);
	}
	free_data(&data);
	free_env(data->env);
	free_set_null((void **)&data->pwd);
	free_set_null((void **)&data);
	exit(status);
}

void	free_close_fd(t_parse *data, int mode, int status, t_pipe *pipes)
{
	free_data(&data);
	free_set_null((void **)&data->pwd);
	ft_free_array(&data->env);
	if (mode == 1)
	{
		if (data->fds)
		{
			close(data->fds->oldfd[0]);
			close(data->fds->oldfd[1]);
			close(data->fds->pfd[0]);
			close(data->fds->pfd[1]);
			free_set_null((void **)&data->fds);
		}
	}
	if (pipes)
	{
		free_set_null((void **)&pipes->pipe_fds);
		free_set_null((void **)&pipes->pid);
	}
	free_set_null((void **)&data->fds);
	free_set_null((void **)&data);
>>>>>>> main
	exit(status);
}

void	print_message(char *cmd, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(message, 2);
}

<<<<<<< HEAD
void	dup2_close(int oldfd[2])
{
	dup2(oldfd[0], 0);
	dup2(oldfd[1], 1);
	close(oldfd[0]);
	close(oldfd[1]);
=======
void	close_new_fd(t_parse *data)
{
	if (data->fds)
	{
		if (data->fds->oldfd[0])
		{
			close(data->fds->oldfd[0]);
			data->fds->oldfd[0] = 0;
		}
		if (data->fds->oldfd[1])
		{
			close(data->fds->oldfd[1]);
			data->fds->oldfd[1] = 0;
		}
		if (data->fds->pfd[0])
		{
			close(data->fds->pfd[0]);
			data->fds->pfd[0] = 0;
		}
		if (data->fds->pfd[1])
		{
			close(data->fds->pfd[1]);
			data->fds->pfd[1] = 0;
		}
	}
>>>>>>> main
}
