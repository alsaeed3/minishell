/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_delegate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:34:20 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/10 13:10:58 by habu-zua         ###   ########.fr       */
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
		ret = handle_single(parser->cmds[0], parser, 0);
	}
	else
	{
		parser->h_index = -1;
		ret = handle_pipe(parser);
	}
	g_signal = 1;
	while (parser->heredocs_num)
	{
		unlink(parser->heredoc_tmp_files[parser->heredocs_num - 1]);
		parser->heredocs_num--;
	}
	parser->exit_status = ret;
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
