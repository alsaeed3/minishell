/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:38:15 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/19 15:24:24 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"
# define FORKED_CHILD 0

static int exec_single_command(char **cmd);
static int handle_pipe(t_parse parser);


void exec_function(t_parse parser)
{
   if (parser.parts_num == 1)
    exec_single_command(parser.cmds[0]);
    else
        handle_pipe(parser);
}
/*
static int pipe_exec(char **cmd)
{
    char *path;
    // int pid = fork();
    // if (pid == -1)
    //     exit(EXIT_FAILURE);
    // else if (pid == 0)
    // {
        path = ft_getpath(cmd[0], getenv("PATH"));
        execve(path, cmd, NULL);
        exit(126);
    // }
    // else
    //     wait(NULL);
    // return 0;
}
*/
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
        exit(126);
    }
    else
        wait(NULL);
    return 0;
}

static int handle_pipe(t_parse parser)
{
    int i = 0;
    int fds[2];
    int pid;
    int status;
    int fd_in = 0;
    char *path;
    printf("parts_num: %d\n", parser.parts_num);
    while (i < parser.parts_num)
    {
        if(i < parser.parts_num - 1)
            pipe(fds);
        pid = fork();
        if (pid == -1)
            exit(EXIT_FAILURE);
        else if (pid == FORKED_CHILD)
        {
            dup2(fd_in, STDIN_FILENO);
            if (i < parser.parts_num - 1)
                dup2(fds[STDOUT_FILENO], STDOUT_FILENO);
            close(fds[0]);
            // pipe_exec(parser.cmds[i]);
            path = ft_getpath(parser.cmds[i][0], getenv("PATH"));
            execve(path, parser.cmds[i], NULL);
            exit(126);
        }
        waitpid(pid, &status, 0);
        printf("status: %d\n", WEXITSTATUS(status));
        close(fds[1]);
        fd_in = fds[0];
        i++;
    }
    return 0;
}
