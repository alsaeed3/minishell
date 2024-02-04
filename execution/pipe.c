/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:16:41 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/04 23:37:50 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

int	handle_pipe(t_parse *parser)
{
	// ft_putendl_fd("handle_pipe", 2);
	int	i;
	int	j;
	int	fds[2];
	int	pid;
	int	fd_in;

	i = -1;
	fd_in = 0;
		

	while (++i < parser->parts_num)
	{
		
		j = -1;
		while (++j < parser->in_rdr_num[i])
		{
			if (!parser->inputs_tokens[i] || !parser->inputs_redirections[i])
				break ;
			if (parser->inputs_tokens[i][j] == 1 && parser->inputs_redirections[i][j + 1] == NULL)
				parser->h_index++;
		}
		if (i < parser->parts_num - 1)
			pipe(fds);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == FORKED_CHILD)
		{
			dup2(fd_in, STDIN_FILENO);
			if (i < parser->parts_num - 1)
				dup2(fds[STDOUT_FILENO], STDOUT_FILENO);
			close(fds[0]);
			handle_single(parser->cmds[i], parser, 1, i);
			
			exit(EXIT_SUCCESS);
		}
		// else
		// {
			waitpid(pid, &parser->exit_status, 0);
			close(fds[1]);
			fd_in = fds[0];
			// ft_putstr_fd("exit status: ", 2);
			// ft_putnbr_fd(parser->exit_status, 2);
		// }
	}
	return (0);
}

void	exit_pipe(t_parse *data)
{
	// free_inputs(data->env);
	// if (g_user_input)
	// 	free(g_user_input);
	free(data->pwd);
	exit(EXIT_SUCCESS);
}
