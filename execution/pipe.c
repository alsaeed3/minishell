/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:16:41 by habu-zua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/08 16:20:10 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/18 23:11:35 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

<<<<<<< HEAD
static void	set_h_index(t_parse *parser, int i)
=======
static void	set_h_index(t_parse *data, int i)
>>>>>>> main
{
	int	j;

	j = -1;
<<<<<<< HEAD
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

	ret = 0;
	oldfd[0] = dup(0);
	oldfd[1] = dup(1);
	if (data->in_rdr_num[x] > 0)
		if (redirect_from(data, x))
			return (1);
	if (data->out_rdr_num[x] > 0)
		redirect_to(data, x);
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
=======
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
>>>>>>> main
	{
		waitpid(pipes.pid[pipes.i], &pipes.ret, 0);
		if (WIFEXITED(pipes.ret))
			pipes.ret = WEXITSTATUS(pipes.ret);
	}
<<<<<<< HEAD
=======
	free_set_null((void **)&pipes.pipe_fds);
	free_set_null((void **)&pipes.pid);
>>>>>>> main
	return (pipes.ret);
}
