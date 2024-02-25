/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:16:41 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/18 23:11:35 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static void	set_h_index(t_parse *data, int i)
{
	int	j;

	j = -1;
	while (++j < data->in_rdr_num[i])
	{
		if (!data->inputs_tokens[i] || !data->inputs_redirections[i])
			break ;
		if (data->inputs_tokens[i][j] == 1 \
		&& data->inputs_redirections[i][j + 1] == NULL)
			data->h_index++;
	}
}

static void	init_t_pipe(t_parse *data, t_pipe *pipes)
{
	*pipes = (t_pipe){0};
	pipes->i = 0;
	pipes->ret = 0;
	pipes->pipe_fds = ft_calloc((data->parts_num - 1), \
	sizeof(*pipes->pipe_fds));
	pipes->pid = ft_calloc(data->parts_num, sizeof(*pipes->pid));
}

void	open_cmds_pipes(t_parse *data, t_pipe *pipes)
{
	pipes->i = -1;
	while (++pipes->i < data->parts_num - 1)
	{
		if (pipe(pipes->pipe_fds[pipes->i]) == -1)
		{
			perror("pipe");
			free (pipes->pipe_fds);
			free_close_fd(data, 1, 1, pipes);
		}
	}
}

t_bool	loop_pipe(t_parse *data, t_pipe *pipes)
{
	set_h_index(data, pipes->i);
	pipes->pid[pipes->i] = fork();
	if (pipes->pid[pipes->i] == -1)
	{
		perror("fork");
		return (TRUE);
	}
	if (pipes->pid[pipes->i] == 0)
	{
		g_signal = 3;
		if (pipes->pid)
			free_set_null((void **)&pipes->pid);
		if (pipes->i != 0)
			dup2(pipes->pipe_fds[pipes->i - 1][0], STDIN_FILENO);
		if (pipes->i != data->parts_num - 1)
			dup2(pipes->pipe_fds[pipes->i][1], STDOUT_FILENO);
		pipes->j = -1;
		while (++pipes->j < data->parts_num - 1)
		{
			close(pipes->pipe_fds[pipes->j][0]);
			close(pipes->pipe_fds[pipes->j][1]);
		}
		handle_single_pipe(data->cmds[pipes->i], data, pipes);
	}
	return (FALSE);
}

int	handle_pipe(t_parse *data)
{
	t_pipe	pipes;

	init_t_pipe(data, &pipes);
	open_cmds_pipes(data, &pipes);
	pipes.i = -1;
	while (++pipes.i < data->parts_num)
		if (loop_pipe(data, &pipes))
			break ;
	pipes.i = -1;
	while (++pipes.i < data->parts_num - 1)
	{
		close(pipes.pipe_fds[pipes.i][0]);
		close(pipes.pipe_fds[pipes.i][1]);
	}
	pipes.i = -1;
	while (++pipes.i < data->parts_num)
	{
		waitpid(pipes.pid[pipes.i], &pipes.ret, 0);
		if (WIFEXITED(pipes.ret))
			pipes.ret = WEXITSTATUS(pipes.ret);
	}
	free_set_null((void **)&pipes.pipe_fds);
	free_set_null((void **)&pipes.pid);
	return (pipes.ret);
}
