/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:06:04 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/11 23:27:09 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	handle_parentps(char *input2, t_data *data, int pid, int *fds)
{
	int		oldfd;
	int		status;

	if (waitpid(pid, &status, 0) != pid)
		exit(EXIT_FAILURE);
	free(data->user_input);
	data->user_input = NULL;
	oldfd = dup(0);
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
	parser_start(input2, data);
	dup2(oldfd, 0);
	close(oldfd);
}

int		handle_pipe(char *input1, char *input2, t_data *data)
{
	pid_t	pid;
	int		fds[2];

	printf("input1: %s\n", input1);
	printf("input2: %s\n", input2);
	if (pipe(fds) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0) // child
	{
		free(input2);
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		handle_basic(input1, data, 1);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		free(input1);
		input1 = NULL;
		handle_parentps(input2, data, pid, fds);
	}
	return (1);
}
