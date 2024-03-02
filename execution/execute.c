/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:38:57 by habu-zua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/09 10:46:37 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/19 17:33:48 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

<<<<<<< HEAD
int	handle_exec(char **inputs, t_parse *data)
{
	int		ret;
	pid_t	pid;

	ret = 0;
	if (!check_exec(inputs, data))
	{
		print_message(inputs[0], ": command not found");
		return (127);
	}
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
>>>>>>> main
	g_signal = 3;
	pid = fork();
	if (pid == 0)
	{
<<<<<<< HEAD
		if (execute(inputs, data) != 0)
			exit(errno);
		free_close_fd(data, 0, 0, 0);
	}
	else if (pid < 0)
		exit(1);
=======
		close_old_fds(data);
		if (execute(inputs, data) != 0)
			free_close_fd(data, 1, errno, NULL);
		free_close_fd(data, 0, 0, NULL);
	}
	else if (pid < 0)
		free_close_fd(data, 1, errno, NULL);
>>>>>>> main
	else
		waitpid(pid, &ret, 0);
	if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	return (ret);
}

<<<<<<< HEAD
void	handle_exec_pipe(char **inputs, t_parse *data, int x)
{
	int	oldfd[2];

	oldfd[0] = dup(0);
	oldfd[1] = dup(1);
	if (data->in_rdr_num[x] > 0)
		if (redirect_from(data, x))
			return ;
	if (data->out_rdr_num[x] > 0)
		redirect_to(data, x);
	if (!check_exec(inputs, data))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(inputs[0], 2);
		ft_putendl_fd(": command not found", 2);
		// rl_clear_history();
		free_close_fd(data, oldfd, 1, 127);
	}
	g_signal = 3;
	if (execute(inputs, data) != 0)
		free_close_fd(data, oldfd, 1, errno);
	free_close_fd(data, oldfd, 1, 0);
}

int	execute(char **inputs, t_parse *data)
{
	int			index;
=======
int	execute(char **inputs, t_parse *data)
{
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
