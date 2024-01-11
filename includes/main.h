#ifndef MAIN_H
#define MAIN_H
#include <curses.h>
#include <termios.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
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

typedef	struct	s_data
{
	char		**env;
	int			fd_in;
	int			fd_out;
	char		*pwd;
	int			redir;
    int			status;
    char		*user_input;
    int			quit;
}				t_data;

#endif