/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:38:57 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/21 16:36:32 by habu-zua         ###   ########.fr       */
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:38:57 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/19 17:33:48 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

<<<<<<< HEAD
void	handle_exec(char **inputs, t_parse *data)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!check_exec(inputs, data))
		return (error_sentence("\t\tminishell: Unknown command\n", 127));
	pid = fork();
	if (pid == 0)
	{
		if (execute(inputs, data) != 0)
			exit(errno);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		// sig_exec_init();
		waitpid(pid, &status, 0);
	}
	// g_status = WEXITSTATUS(status);
	// if (g_quit)
	// 	g_status = 130;
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

	index = var_index("PATH=", data);
	if (ft_strchr(inputs[0], '/') && (access(inputs[0], X_OK) == 0))
		{
			if (execve(inputs[0], &inputs[0], data->env) != -1)
				return 0;
		}
		else if (index >= 0)
		{
			if (!execute_2(inputs, data))
				return 0;
		}
=======
	int	index;

	index = var_index("PATH=", data);
	if (ft_strchr(inputs[0], '/') && (access(inputs[0], X_OK) == 0))
	{
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
		if (execve(inputs[0], &inputs[0], data->env) != -1)
			return (0);
	}
	else if (index >= 0)
	{
		if (!execute_2(inputs, data))
			return (0);
	}
>>>>>>> main
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
<<<<<<< HEAD
		if (access(paths[i], X_OK) == 0 && 
			execve(paths[i], inputs, data->env) != -1)
            return 0;
=======
		if (access(paths[i], X_OK) == 0
			&& execve(paths[i], &inputs[0], data->env) != -1)
			return (0);
>>>>>>> main
		i++;
	}
	return (1);
}
