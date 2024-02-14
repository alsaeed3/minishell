/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_delegate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:34:20 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/14 20:58:45 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	exec_delegator(t_parse **data)
{
	int	ret;
	int	hrnum;

	ret = 0;
	hrnum = (*data)->heredocs_num;
	if ((*data)->parts_num == 1)
	{
		(*data)->h_index = 0;
		ret = handle_single((*data)->cmds[0], *data, 0);
	}
	else
	{
		(*data)->h_index = -1;
		ret = handle_pipe((*data));
	}
	g_signal = 1;
	while (hrnum)
	{
		if (access((*data)->heredoc_tmp_files[hrnum - 1], F_OK) == 0)
			unlink((*data)->heredoc_tmp_files[hrnum - 1]);
		hrnum--;
	}
	(*data)->exit_status = ret;
}

int	handle_single(char **inputs, t_parse *data, int x)
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
	if (inputs[0])
		ret = choose_action(inputs, data, x);
	dup2(data->fds->oldfd[0], 0);
	close(data->fds->oldfd[0]);
	dup2(data->fds->oldfd[1], 1);
	close(data->fds->oldfd[1]);
	// close_fds(data);
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
		ret = handle_exec(cmd, data);
	return (ret);
}
