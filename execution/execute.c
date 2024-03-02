/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:38:57 by habu-zua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/31 00:35:11 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/19 17:33:48 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

<<<<<<< HEAD
void	handle_exec(char **inputs, t_parse *data)
{
	pid_t	pid;

	if (!check_exec(inputs, data))
	{
		data->exit_status = 127;
		ft_error("\t\tminishell: Unknown command\n");
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		g_signal = 3;
		if (execute(inputs, data) != 0)
			exit(errno);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
		waitpid(pid, &data->exit_status, 0);
=======
static void	close_old_fds(t_parse *data)
{
	if (data->fds)
	{
		if (data->fds->oldfd[0])
			close(data->fds->oldfd[0]);
		if (data->fds->oldfd[1])
			close(data->fds->oldfd[1]);
	}
}

int	handle_exec(char **inputs, t_parse *data)
{
	int			ret;
	pid_t		pid;

	ret = 0;
	ret = check_exec_file(inputs, data);
	if (ret)
		return (ret);
	g_signal = 3;
	pid = fork();
	if (pid == 0)
	{
		close_old_fds(data);
		if (execute(inputs, data) != 0)
			free_close_fd(data, 1, errno, NULL);
		free_close_fd(data, 0, 0, NULL);
	}
	else if (pid < 0)
		free_close_fd(data, 1, errno, NULL);
	else
		waitpid(pid, &ret, 0);
	if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	return (ret);
>>>>>>> main
}

int	execute(char **inputs, t_parse *data)
{
<<<<<<< HEAD
	int			index;
=======
	int	index;
>>>>>>> main

	index = var_index("PATH=", data);
	if (ft_strchr(inputs[0], '/') && (access(inputs[0], X_OK) == 0))
	{
<<<<<<< HEAD
=======
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
>>>>>>> main
		if (execve(inputs[0], &inputs[0], data->env) != -1)
			return (0);
	}
	else if (index >= 0)
	{
		if (!execute_2(inputs, data))
			return (0);
	}
	return (1);
}

int	execute_2(char **inputs, t_parse *data)
{
	int			i;
	char		**paths;
	int			index;

<<<<<<< HEAD
=======
	if (data->fds->oldfd[0])
		close(data->fds->oldfd[0]);
	if (data->fds->oldfd[1])
		close(data->fds->oldfd[1]);
	if (data->fds->pfd[0])
		close(data->fds->pfd[0]);
	if (data->fds->pfd[1])
		close(data->fds->pfd[1]);
>>>>>>> main
	i = 0;
	index = var_index("PATH=", data);
	paths = gen_paths(index, data, inputs[0]);
	while (paths[i])
	{
		if (access(paths[i], X_OK) == 0
<<<<<<< HEAD
			&& execve(paths[i], inputs, data->env) != -1)
=======
			&& execve(paths[i], &inputs[0], data->env) != -1)
>>>>>>> main
			return (0);
		i++;
	}
	return (1);
}
<<<<<<< HEAD


/*
127: command not found
126: permission denied
128: invalid argument
130: ctrl + c

*/
=======
>>>>>>> main
