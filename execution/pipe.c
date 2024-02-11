/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:16:41 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/11 19:28:43 by habu-zua         ###   ########.fr       */
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

void	init_t_pipe(t_pipe *pipes)
{
	*pipes = (t_pipe){0};
	pipes->i = -1;
	pipes->fd_in = 0;
	pipes->ret = 0;
}

static void	piping(t_parse *data, t_pipe *pipes)
{
	set_h_index(data, pipes->i);
	if (pipes->i < data->parts_num - 1)
		pipe(data->fds->pfd);
	g_signal = 3;
	pipes->pid[pipes->i] = fork();
	if (pipes->pid[pipes->i] == -1)
		free_close_fd(data, 1, 1);
	else if (pipes->pid[pipes->i] == 0)
	{
		dup2(pipes->fd_in, 0);
		// if (pipes->i < data->parts_num - 1)
			close(data->fds->pfd[0]);
		dup2(data->fds->pfd[1], 1);
		close(data->fds->pfd[1]);
		pipes->ret = handle_single_pipe(data->cmds[pipes->i], data, pipes->i);
		free_close_fd(data, 1, pipes->ret);
	}
	close(data->fds->pfd[1]);
	if (pipes->fd_in)
		close(pipes->fd_in);
	pipes->fd_in = data->fds->pfd[0];
}

int	handle_pipe(t_parse *data)
{
	t_pipe	pipes;

	init_t_pipe(&pipes);
	while (++pipes.i < data->parts_num)
		piping(data, &pipes);
	close_fds(data);
	pipes.i = -1;
	while (++pipes.i < data->parts_num)
	{
		waitpid(pipes.pid[pipes.i], &pipes.ret, 0);
		if (WIFEXITED(pipes.ret))
			pipes.ret = WEXITSTATUS(pipes.ret);
	}
	return (pipes.ret);
}
