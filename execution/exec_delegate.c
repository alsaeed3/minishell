/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_delegate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:34:20 by habu-zua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/21 15:58:35 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/21 16:09:43 by alsaeed          ###   ########.fr       */
>>>>>>> main
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
		ret = handle_single((*data)->cmds[0], *data);
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
	if ((*data)->heredoc_tmp_files)
		ft_free_array(&(*data)->heredoc_tmp_files);
	(*data)->exit_status = ret;
}

void	close_some_fds(t_parse *data)
{
	if (data->fds)
	{
		dup2(data->fds->oldfd[0], 0);
		close(data->fds->oldfd[0]);
		dup2(data->fds->oldfd[1], 1);
		close(data->fds->oldfd[1]);
	}
}

int	handle_single(char **inputs, t_parse *data)
{
	int	ret;

	ret = 0;
	data->fds->oldfd[0] = dup(0);
	data->fds->oldfd[1] = dup(1);
	if (data->out_rdr_num[0] > 0)
	{
		ret = redirect_to(data);
		if (ret == 1)
			return (1);
		else if (ret == 126)
			return (126);
		else if (ret == 127)
			return (127);
	}
	if (data->in_rdr_num[0] > 0)
	{
		if (redirect_from(data))
			return (1);
	}
	if (inputs[0])
		ret = choose_action(inputs, data);
	close_some_fds(data);
	return (ret);
}

int	choose_action(char **cmd, t_parse *data)
{
	int		ret;

	ret = 0;
	if (ft_strcmp(cmd[0], "echo") == 0)
		handle_echo(data, 0);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		handle_pwd(data);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ret = handle_cd(cmd, data);
	else if (ft_strcmp(cmd[0], "env") == 0)
		handle_env(data->env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		handle_exit(cmd, data, NULL, 0);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ret = handle_export(cmd, data, 1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ret = handle_unset(cmd, data);
	else if (ft_strchr(cmd[0], '='))
		ret = handle_export(cmd, data, 0);
	else
		ret = handle_exec(cmd, data);
	return (ret);
}
