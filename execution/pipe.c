/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:16:41 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/05 21:20:44 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static void set_h_index(t_parse *parser, int i)
{
	int j;
	
	j = -1;
	while (++j < parser->in_rdr_num[i])
	{
		if (!parser->inputs_tokens[i] || !parser->inputs_redirections[i])
			break ;
		if (parser->inputs_tokens[i][j] == 1 && parser->inputs_redirections[i][j + 1] == NULL)
			parser->h_index++;
	}
}

int	handle_pipe(t_parse *parser)
{
	int	i;
	int	fds[2];
	int	pid;
	int	fd_in;
	int	ret;

	i = -1;
	ret = 0;
	fd_in = 0;
	while (++i < parser->parts_num)
	{
		set_h_index(parser, i);
		if (i < parser->parts_num - 1)
			pipe(fds);
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid == 0)
		{
			dup2(fd_in, 0);
			if (i < parser->parts_num - 1)
				dup2(fds[1], 1);
			close(fds[0]);
			ret = handle_single(parser->cmds[i], parser, 1, i);
			exit(ret);
		}
		waitpid(pid, &ret, 0);
		if(WIFEXITED(ret))
			ret = WEXITSTATUS(ret);
		close(fds[1]);
		fd_in = fds[0];
	}
	return (ret);
}

void	exit_pipe(t_parse *data)
{
	// free_inputs(data->env);
	// if (g_user_input)
	// 	free(g_user_input);
	free(data->pwd);
	exit(0);
}
