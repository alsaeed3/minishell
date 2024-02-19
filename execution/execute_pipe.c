/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:01:20 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/19 17:36:22 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	handle_single_pipe(char **inputs, t_parse *data, t_pipe *pipes)
{
	int		fd;

	fd = 0;
	if (data->in_rdr_num[pipes->i] > 0)
		fd = redirect_from_pipe(data, pipes);
	ft_free_array(&data->heredoc_tmp_files);
	free_set_null((void **)&data->heredoc_tmp_files);
	if (data->out_rdr_num[pipes->i] > 0)
		fd = redirect_to_pipe(data, pipes);
	if (inputs && inputs[0])
		choose_action_pipe(inputs, data, pipes, fd);
	ft_free_array(&data->heredoc_tmp_files);
	close(fd);
	close_fds(data);
	free_set_null((void **)&data->fds);
	free_set_null((void **)&pipes->pipe_fds);
	free_set_null((void **)&pipes->pid);
	free_close_fd(data, 0, 0, pipes);
}

void	choose_action_pipe(char **cmd, t_parse *data, t_pipe *pipes, int fd)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd[0], "echo") == 0)
		handle_echo(data, pipes->i);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		handle_pwd(data);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ret = handle_cd(cmd, data);
	else if (ft_strcmp(cmd[0], "env") == 0)
		handle_env(data->env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		handle_exit(cmd, data);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ret = handle_export(cmd, data);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ret = handle_unset(cmd, data);
	else
		ret = handle_exec_pipe(cmd, data, pipes);
	close(fd);
	close_fds(data);
	free_set_null((void **)&data->fds);
	free_set_null((void **)&pipes->pipe_fds);
	free_set_null((void **)&pipes->pid);
	free_close_fd(data, 0, ret, pipes);
}

int	handle_exec_pipe(char **inputs, t_parse *data, t_pipe *pipes)
{
	int			ret;

	ret = 0;
	ret = check_exec_file(inputs, data);
	if (ret)
		return (ret);
	g_signal = 3;
	if (execute(inputs, data) != 0)
		free_close_fd(data, 0, errno, pipes);
	return (ret);
}

int	execute_pipe(char **inputs, t_parse *data)
{
	int			index;

	index = var_index("PATH=", data);
	if (ft_strchr(inputs[0], '/') && (access(inputs[0], X_OK) == 0))
	{
		if (execve(inputs[0], &inputs[0], data->env) != -1)
			return (0);
	}
	else if (index >= 0)
	{
		if (!execute_2_pipe(inputs, data))
			return (0);
	}
	return (1);
}

int	execute_2_pipe(char **inputs, t_parse *data)
{
	int			i;
	char		**paths;
	int			index;

	i = 0;
	index = var_index("PATH=", data);
	paths = gen_paths(index, data, inputs[0]);
	while (paths[i])
	{
		if (access(paths[i], X_OK) == 0
			&& execve(paths[i], &inputs[0], data->env) != -1)
			return (0);
		i++;
	}
	return (1);
}
