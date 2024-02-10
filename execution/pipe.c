/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:16:41 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/10 11:57:36 by habu-zua         ###   ########.fr       */
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

int	handle_single(char **inputs, t_parse *data, int x)
{
	int	oldfd[2];
	int	ret;
	
	expand_dolar_sign(inputs, data);
	
	ret = 0;
	oldfd[0] = dup(0);
	oldfd[1] = dup(1);
	if (data->in_rdr_num[x] > 0)
		if (redirect_from(data, x))
			return (1);
	if (data->out_rdr_num[x] > 0)
		if (redirect_to(data, x))
			return (127);
	ret = choose_action(inputs, data, x);
	dup2(oldfd[0], 0);
	dup2(oldfd[1], 1);
	close_fds(data);
	close(oldfd[0]);
	close(oldfd[1]);
	return (ret);
}

static void	piping(t_parse *parser, t_pipe *pipes)
{
	set_h_index(parser, pipes->i);
	if (pipes->i < parser->parts_num - 1)
		pipe(pipes->fds);
	g_signal = 3;
	pipes->pid[pipes->i] = fork();
	if (pipes->pid[pipes->i] == -1)
		free_close_fd(parser, pipes->fds, 1, 1);
	else if (pipes->pid[pipes->i] == 0)
	{
		dup2(pipes->fd_in, 0);
		if (pipes->i < parser->parts_num - 1)
			close(pipes->fds[0]);
		dup2(pipes->fds[1], 1);
		pipes->ret = handle_single(parser->cmds[pipes->i], parser, pipes->i);
		free_close_fd(parser, pipes->fds, 1, pipes->ret);
	}
	close(pipes->fds[1]);
	if (pipes->fd_in)
		close(pipes->fd_in);
	pipes->fd_in = pipes->fds[0];
}

int	handle_pipe(t_parse *parser)
{
	t_pipe	pipes;

	init_t_pipe(&pipes);
	while (++pipes.i < parser->parts_num)
	{
		piping(parser, &pipes);
	}
	pipes.i = -1;
	while (++pipes.i < parser->parts_num)
	{
		waitpid(pipes.pid[pipes.i], &pipes.ret, 0);
		if (WIFEXITED(pipes.ret))
			pipes.ret = WEXITSTATUS(pipes.ret);
	}
	return (pipes.ret);
}
