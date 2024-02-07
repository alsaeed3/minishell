/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:38:57 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/07 16:54:23 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

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
	pid = fork();
	if (pid == 0)
	{
		g_signal = 3;
		if (execute(inputs, data) != 0)
			exit(errno);
		free_close_fd(data, 0, 0, 0);
	}
	else if (pid < 0)
		exit(1);
	else
		waitpid(pid, &ret, 0);
	if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	return (ret);
}

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

	index = var_index("PATH=", data);
	if (ft_strchr(inputs[0], '/') && (access(inputs[0], X_OK) == 0))
	{
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

	i = 0;
	index = var_index("PATH=", data);
	paths = gen_paths(index, data, inputs[0]);
	while (paths[i])
	{
		if (access(paths[i], X_OK) == 0
			&& execve(paths[i], inputs, data->env) != -1)
			return (0);
		i++;
	}
	return (1);
}
