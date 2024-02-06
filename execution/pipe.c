/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:16:41 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/06 21:02:33 by alsaeed          ###   ########.fr       */
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
	int	pid[2048];
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
		pid[i] = fork();
		if (pid[i] == -1)
			exit(1);
		else if (pid[i] == 0)
		{
			dup2(fd_in, 0);
			if (i < parser->parts_num - 1)
				dup2(fds[1], 1);
			close(fds[0]);
			if (is_built_in(parser->cmds[i][0]))
			{
				choose_built_in(parser->cmds[i], parser, i);
				free_parser(&parser);
				free_set_null(parser->pwd);
				ft_free_array(parser->env);
				free_set_null(parser);
				exit(EXIT_SUCCESS);
			}
			else
				ret = handle_exec_pipe(parser->cmds[i], parser, i);
		}
	}
	i = -1;
	while (++i < parser->parts_num)
		waitpid(pid[i], &ret, 0);
	if(WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	close(fds[1]);
	fd_in = fds[0];
	return (ret);
}

void	exit_pipe(t_parse *data)
{
	// free_inputs(data->env);
	// if (g_user_input)
	// 	free(g_user_input);
	free_set_null(data->pwd);
	exit(0);
}
