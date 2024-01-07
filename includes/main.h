#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h> 
#include "../lib/inc/libft.h"
#include <fcntl.h> //for open

void    ft_free(char **cmd);
char    *ft_getpath(char *cmd, char *envpath);
void    ft_print_cmd(char **cmd);
void	ft_trim_input(char **input);



#endif