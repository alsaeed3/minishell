/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:45:17 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/07 17:21:07 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//this main can execute commands with pipes (multiple pipes) 
// still implementing redirections.

#include "./includes/main.h"
#include <string.h>
#include <sys/stat.h>
#include <sys/errno.h>

#define FORKED_CHILD 0

typedef struct Context
{
    int fd[2]; // for stdin and stdout
    int fd_close; // close and fd? -1 if not
} Context;

static int exec_cmd(char *cmd, Context *ctx);
static int exec_pipe(char *cmd, Context *ctx);
static int exec_command(char *cmd, Context *ctx);
char *ft_strtrim(const char *s);

void exec(char *cmd)
{
    Context ctx = {
        {
            STDIN_FILENO,
            STDOUT_FILENO
        },
        -1
    };

    int children = exec_cmd(cmd, &ctx);
    printf("children: %d\n", children);
    for (int i = 0; i < children; i++)
    {
        wait(NULL);
    }
	free(cmd);
}

static int exec_cmd(char *cmd, Context *ctx)
{
    if (ft_strchr(cmd, '|'))
        return exec_pipe(cmd, ctx);
    else if (cmd[0] != '\0')
        return exec_command(cmd, ctx);
    else
        return 0;
}

static int exec_pipe(char *cmd, Context *ctx)
{
    int p[2];
    pipe(p);

    int children = 0;
    char *lhs = ft_strndup(cmd, ft_strchr(cmd, '|') - cmd);
    char *rhs = ft_strchr(cmd, '|') + 1;
    
	Context lhs_ctx = *ctx;
    lhs_ctx.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
    lhs_ctx.fd_close = p[STDIN_FILENO];
    children += exec_cmd(lhs, &lhs_ctx);
    close(p[STDOUT_FILENO]);
    
    Context rhs_ctx = *ctx;
    rhs_ctx.fd[STDIN_FILENO] = p[STDIN_FILENO];
    rhs_ctx.fd_close = p[STDOUT_FILENO];
    children += exec_cmd(rhs, &rhs_ctx);
	close(p[STDIN_FILENO]);

	free(lhs);
	// free(rhs); no memory allocated for rhs
    return children;
}
/*
static int exec_command(char *cmd, Context *ctx)
{
    printf("cmd: %s\n", cmd);
    if (fork() == FORKED_CHILD)
    {
        dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
        dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
        if (ctx->fd_close != -1)
            close(ctx->fd_close);
        char **argv = ft_split(cmd, ' ');
        char *command = ft_getpath(argv[0], getenv("PATH"));
        execve(command, argv, NULL);
        perror("execve"); // In case execve fails
        exit(EXIT_FAILURE);
    }
    return 1;
}
*/
#include <sys/stat.h>

// ...

static int exec_command(char *cmd, Context *ctx)
{
    printf("cmd: %s\n", cmd);

    char **argv = ft_split(cmd, ' ');

    int i = 0;
    while (argv[i] != NULL) {
        if (strcmp(argv[i], "<") == 0) {
            // Input redirection
            if (argv[i + 1] != NULL) {
                int input_fd = open(argv[i + 1], O_RDONLY);
                if (input_fd == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }
            break;
        } else if (strcmp(argv[i], ">") == 0) {
            // Output redirection
            if (argv[i + 1] != NULL) {
                int output_fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (output_fd == -1) {
                    if (errno == ENOENT) {
                        // If the file does not exist, create it
                        int create_fd = creat(argv[i + 1], 0666);
                        if (create_fd == -1) {
                            perror("creat");
                            exit(EXIT_FAILURE);
                        }
                        close(create_fd);
                        output_fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    } else {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                }
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
            }
            break;
        } else if (strcmp(argv[i], ">>") == 0) {
            // Append output redirection
            if (argv[i + 1] != NULL) {
                int output_fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
                if (output_fd == -1) {
                    if (errno == ENOENT) {
                        // If the file does not exist, create it
                        int create_fd = creat(argv[i + 1], 0666);
                        if (create_fd == -1) {
                            perror("creat");
                            exit(EXIT_FAILURE);
                        }
                        close(create_fd);
                        output_fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
                    } else {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                }
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
            }
            break;
        }
        i++;
    }

    if (fork() == FORKED_CHILD) {
        // Restore default stdin and stdout for the child process
        dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
        dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);

        if (ctx->fd_close != -1) {
            close(ctx->fd_close);
        }
		
        char *command = ft_getpath(argv[0], getenv("PATH"));
        execve(command, argv, NULL);
        perror("execve"); // In case execve fails
        exit(EXIT_FAILURE);
    }

    ft_free(argv);

    return 1;
}



int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char *input;
    char **cmd;
    char *path;

    path = 0;
    input = NULL;
    while (1)
    {
        input = readline("$> ");
        if (ft_strcmp(input, "exit") == 0)
        {
            free(input);
            exit(0);
        }
        exec(input);
    }
    return (0);
}


/*
	this part to test leaks if file not closed.
	int fd = open("test.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	close(fd);

*/
