/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:01:20 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/11 13:28:07 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/exec.h"

int	execute_2_pipe(char **inputs, t_parse *data);
int	choose_action_pipe(char **cmd, t_parse *data, int x);
int	handle_exec_pipe(char **inputs, t_parse *data);
int	execute_pipe(char **inputs, t_parse *data);
int	execute_2_pipe(char **inputs, t_parse *data);

int	handle_single_pipe(char **inputs, t_parse *data, int x)
{
	int	ret;

	expand_dolar_sign(inputs, data);

	ret = 0;
	data->fds->oldfd[0] = dup(0);
	data->fds->oldfd[1] = dup(1);
	if (data->in_rdr_num[x] > 0)
		if (redirect_from(data, x))
			return (1);
	if (data->out_rdr_num[x] > 0)
    {
		ret = redirect_to(data, x);
		if (ret == 127)
			return (127);
		else if (ret == 1)
			return (0);
	}
	ret = choose_action_pipe(inputs, data, x);
	dup2(data->fds->oldfd[0], 0);
	close(data->fds->oldfd[0]);
	dup2(data->fds->oldfd[1], 1);
	close(data->fds->oldfd[1]);
	close_fds(data);
	return (ret);
}

int	choose_action_pipe(char **cmd, t_parse *data, int x)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd[0], "echo") == 0)
		handle_echo(data, x);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		handle_pwd(data);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		handle_cd(cmd, data);
	else if (ft_strcmp(cmd[0], "env") == 0)
		handle_env(data->env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		handle_exit(cmd, data);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ret = handle_export(cmd, data);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		handle_unset(cmd, data);
	else
		ret = handle_exec_pipe(cmd, data);
	return (ret);
}

int	handle_exec_pipe(char **inputs, t_parse *data)
{
	int		ret;

	ret = 0;
	if (!check_exec(inputs, data))
	{
		print_message(inputs[0], ": command not found");
		return (127);
	}
	g_signal = 3;
	if(data->fds)
    {
        close(data->fds->oldfd[0]);
        close(data->fds->oldfd[1]);
        close(data->fds->pfd[0]);
        close(data->fds->pfd[1]);
    }
    
    if (execute(inputs, data) != 0)
        exit(errno);
    free_close_fd(data, 0, 0);

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
