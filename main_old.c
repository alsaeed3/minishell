/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:45:17 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/07 16:47:38 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/main.h"
#include <string.h>

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

	// Remove the trailing newline character
    cmd[strcspn(cmd, "\n")] = '\0';
	
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
static int exec_command(char *cmd, Context *ctx)
{
    printf("cmd: %s\n", cmd);
    if (fork() == FORKED_CHILD)
    {
        dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
        dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
        if (ctx->fd_close != -1)
        {
            close(ctx->fd_close);
        }
        char **argv = ft_split(cmd, ' ');
        char *command = ft_getpath(argv[0], getenv("PATH"));
        execve(command, argv, NULL);
        perror("execve"); // In case execve fails
        exit(EXIT_FAILURE);
    }
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



// this is extra function not used in the main

#include <stdlib.h>

char *ft_strtrim(const char *s)
{
    if (s == NULL)
        return NULL;

    // Find the start of non-whitespace characters
    size_t start = 0;
    while (s[start] && (s[start] == ' ' || s[start] == '\t' || s[start] == '\n'))
        start++;

    // Find the end of non-whitespace characters
    size_t end = start;
    while (s[end])
        end++;

    // Move backward to find the last non-whitespace character
    while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t' || s[end - 1] == '\n'))
        end--;

    // Allocate and copy the trimmed string
    char *trimmed = (char *)malloc(end - start + 1);
    if (trimmed == NULL)
        return NULL;

    for (size_t i = 0; i < end - start; i++)
        trimmed[i] = s[start + i];
    
    trimmed[end - start] = '\0';

    return trimmed;
}