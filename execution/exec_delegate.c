/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_delegate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:34:20 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/06 18:40:03 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	exec_delegator(t_parse *parser)
{
	int	ret;
	
	ret = 0;
	if (parser->parts_num == 1)
	{
		parser->h_index = 0;
		ret = handle_single(parser->cmds[0], parser, 0, 0);
	}
	else
	{
		parser->h_index = -1;
		ret = handle_pipe(parser);
	}
	while(parser->heredocs_num)
	{
		unlink(parser->heredoc_tmp_files[parser->heredocs_num - 1]);
		parser->heredocs_num--;
	}
	parser->exit_status = ret;
}

int	handle_single(char **inputs, t_parse *data, int piped, int x)
{
	(void)piped;
	int		oldfd[2];
	int ret;

	ret = 0;
	oldfd[0] = dup(0);
	oldfd[1] = dup(1);
	if (data->in_rdr_num[x] > 0)
		if(redirect_from(data, x))
			return (1);
	if (data->out_rdr_num[x] > 0)
		redirect_to(data, x);
	ret = choose_action(inputs, data, x);
	dup2(oldfd[0], 0);
	dup2(oldfd[1], 1);
	close_fds(data);
	close(oldfd[0]);
	close(oldfd[1]);
	// if (piped)
	// 	exit_pipe(data);
	return (ret);
}

int	handle_single_pipe(char **inputs, t_parse *data, int piped, int x)
{
	(void)piped;
	int		oldfd[2];
	int ret;

	ret = 0;
	oldfd[0] = dup(0);
	oldfd[1] = dup(1);
	if (data->in_rdr_num[x] > 0)
		if(redirect_from(data, x))
			return (1);
	if (data->out_rdr_num[x] > 0)
		redirect_to(data, x);
	ret = choose_action(inputs, data, x);
	dup2(oldfd[0], 0);
	dup2(oldfd[1], 1);
	close_fds(data);
	close(oldfd[0]);
	close(oldfd[1]);
	// if (piped)
	// 	exit_pipe(data);
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
		handle_export(cmd, data);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		handle_unset(cmd, data);
	else
		ret = handle_exec(cmd, data);
	return (ret);
}

void	choose_built_in(char **cmd, t_parse *data, int x)
{
	int		oldfd[2];

	oldfd[0] = dup(0);
	oldfd[1] = dup(1);
	if (data->in_rdr_num[x] > 0)
		if(redirect_from(data, x))
			return ;
	if (data->out_rdr_num[x] > 0)
		redirect_to(data, x);
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
		handle_export(cmd, data);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		handle_unset(cmd, data);
	dup2(oldfd[0], 0);
	dup2(oldfd[1], 1);
	close_fds(data);
	close(oldfd[0]);
	close(oldfd[1]);
}

t_bool	is_built_in(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd, "env") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd, "export") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (TRUE);
	return (FALSE);
}

// int	ret_execute(char **cmd, t_parse *data)
// {
// 	int	ret;
	
// 	ret = 0;
// 	ret = handle_exec_pipe(cmd, data);
// 	return (ret);
// }