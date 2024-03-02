/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:26:04 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/20 17:27:40 by habu-zua         ###   ########.fr       */
=======
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:26:04 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/21 17:00:19 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

<<<<<<< HEAD
void   free_exit(t_parse *data, int status)
{
    free_env(data->env);
    free(data->pwd);
    exit(status);
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
	exit(status);
}

void	print_message(char *cmd, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(message, 2);
}

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
