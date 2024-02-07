/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:16:41 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/07 16:45:10 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static void	set_h_index(t_parse *parser, int i)
{
	int	j;

	j = -1;
	while (++j < parser->in_rdr_num[i])
	{
		if (!parser->inputs_tokens[i] || !parser->inputs_redirections[i])
			break ;
		if (parser->inputs_tokens[i][j] == 1 \
		&& parser->inputs_redirections[i][j + 1] == NULL)
			parser->h_index++;
	}
}

void	init_t_pipe(t_pipe *pipes)
{
	*pipes = (t_pipe){0};
	pipes->i = -1;
	pipes->fd_in = 0;
	pipes->ret = 0;
}

int	handle_pipe(t_parse *parser)
{
	t_pipe	pipes;

	init_t_pipe(&pipes);
	while (++pipes.i < parser->parts_num)
	{
		set_h_index(parser, pipes.i);
		if (pipes.i < parser->parts_num - 1)
			pipe(pipes.fds);
		pipes.pid[pipes.i] = fork();
		if (pipes.pid[pipes.i] == -1)
			exit(1);
		else if (pipes.pid[pipes.i] == 0)
			handle_pipe_child(parser, &pipes);
	}
	pipes.i = -1;
	while (++pipes.i < parser->parts_num)
		waitpid(pipes.pid[pipes.i], &pipes.ret, 0);
	if (WIFEXITED(pipes.ret))
		pipes.ret = WEXITSTATUS(pipes.ret);
	close(pipes.fds[1]);
	pipes.fd_in = pipes.fds[0];
	return (pipes.ret);
}

void	handle_pipe_child(t_parse *parser, t_pipe *pipes)
{
	dup2(pipes->fd_in, 0);
	if (pipes->i < parser->parts_num - 1)
		dup2(pipes->fds[1], 1);
	close(pipes->fds[0]);
	if (is_built_in(parser->cmds[pipes->i][0]))
	{
		choose_built_in(parser->cmds[pipes->i], parser, pipes->i);
		free_parser(&parser);
		free_set_null(parser->pwd);
		ft_free_array(parser->env);
		free_set_null(parser);
		exit(EXIT_SUCCESS);
	}
	else
		handle_exec_pipe(parser->cmds[pipes->i], \
		parser, pipes->i);
}

void	choose_built_in(char **cmd, t_parse *data, int x)
{
	int		oldfd[2];

	oldfd[0] = dup(0);
	oldfd[1] = dup(1);
	if (data->in_rdr_num[x] > 0)
		if (redirect_from(data, x))
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
	dup2_close(oldfd);
}
