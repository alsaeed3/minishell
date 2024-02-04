/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_delegate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:34:20 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/04 17:06:38 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	exec_delegator(t_parse *parser)
{
	if (parser->parts_num == 1)
	{
		parser->h_index = 0;
		handle_single(parser->cmds[0], parser, 0, 0);
	}
	else
	{
		parser->h_index = -1;
		handle_pipe(parser);
	}

	while(parser->heredocs_num)
	{
		unlink(parser->heredoc_tmp_files[parser->heredocs_num - 1]);
		parser->heredocs_num--;
	}
	

}

int	handle_single(char **inputs, t_parse *data, int piped, int x)
{
	(void)piped;
	// ft_putendl_fd("handle_single", 2);
	int		oldfd[2];

	oldfd[0] = dup(0);
	oldfd[1] = dup(1);
	if (data->in_rdr_num[x] > 0)
		if(redirect_from(data, x))
			return (0);
	if (data->out_rdr_num[x] > 0)
		redirect_to(data, x);
	choose_action(inputs, data, x);
	dup2(oldfd[0], 0);
	dup2(oldfd[1], 1);
	close_fds(data);
	close(oldfd[0]);
	close(oldfd[1]);
	// if (piped)
	// 	exit_pipe(data);
	return (0);
}

void	choose_action(char **cmd, t_parse *data, int x)
{
	
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
		handle_exec(cmd, data);
}
