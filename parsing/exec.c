/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:38:15 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/12 20:56:40 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/exec.h"
# define FORKED_CHILD 0

static int exec_single_command(char **cmd);
static int hadle_pipe(t_parse parser);


void exec_function(t_parse parser)
{
   if (parser.parts_num == 1)
    exec_single_command(parser.cmds[0]);
    else
        hadle_pipe(parser);
}

static int exec_single_command(char **cmd)
{
    char *path;
    int pid = fork();
    if (pid == -1)
        exit(EXIT_FAILURE);
    else if (pid == 0)
    {
        path = ft_getpath(cmd[0], getenv("PATH"));
        
        execve(path, cmd, NULL);
        exit(EXIT_FAILURE);
    }
    else
        wait(NULL);
    return 0;
}

static int hadle_pipe(t_parse parser)
{
    int i = 0;
    int fds[2];
    int pid;
    int status;
    int fd_in = 0;
    while (i < parser.parts_num)
    {
        pipe(fds);
        pid = fork();
        if (pid == -1)
            exit(EXIT_FAILURE);
        else if (pid == FORKED_CHILD)
        {
            dup2(fd_in, 0);
            if (i < parser.parts_num - 1)
                dup2(fds[1], 1);
            close(fds[0]);
            exec_single_command(parser.cmds[i]);
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(pid, &status, 0);
            close(fds[1]);
            fd_in = fds[0];
            i++;
        }
    }
    return 0;
}
/*
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
*/