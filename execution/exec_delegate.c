/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_delegate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:34:20 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/11 14:32:00 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	exec_delegator(t_parse *data)
{
	int	ret;

	ret = 0;
	if (data->parts_num == 1)
	{
		data->h_index = 0;
		ret = handle_single(data->cmds[0], data, 0);
	}
	else
	{
		data->h_index = -1;
		ret = handle_pipe(data);
	}
	g_signal = 1;
	while (data->heredocs_num)
	{
		unlink(data->heredoc_tmp_files[data->heredocs_num - 1]);
		data->heredocs_num--;
	}
	data->exit_status = ret;
}


int	handle_single(char **inputs, t_parse *data, int x)
{
	int	ret;

	expand_dolar_sign(inputs, data);

	ret = 0;
	if ((data->fds->oldfd[0] = dup(0)) == -1)
		ft_putendl_fd("dup failed", 2);
	if ((data->fds->oldfd[1] = dup(1)) == -1)
		ft_putendl_fd("dup failed", 2);
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
	ret = choose_action(inputs, data, x);
	if (dup2(data->fds->oldfd[0], 0) == -1)
		ft_putendl_fd("dup2 failed", 2);
	close(data->fds->oldfd[0]);
	if (dup2(data->fds->oldfd[1], 1) == -1)
		ft_putendl_fd("dup2 failed", 2);
	close(data->fds->oldfd[1]);
	close_fds(data);
	return (ret);
}

int	choose_action(char **cmd, t_parse *data, int x)
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
		ret = handle_exec(cmd, data);
	return (ret);
}
