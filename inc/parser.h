/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:27:45 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/19 22:39:18 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// # include "exec.h"

# include "../libft/inc/libft.h"	// libft library
# include <stdio.h>       			// printf
# include <stdlib.h>      			// malloc, free, exit
# include <unistd.h>      			// write, access, fork, execve, getpid
# include <sys/types.h>   			// pid_t
# include <sys/wait.h>    			// wait, waitpid, wait3, wait4
# include <signal.h>      			// signal, sigaction, sigemptyset, sigaddset, kill
# include <errno.h>       			// perror, strerror
# include <fcntl.h>       			// open, close, dup, dup2, pipe
# include <sys/stat.h>   			// stat, lstat, fstat
# include <dirent.h>      			// opendir, readdir, closedir
# include <unistd.h>      			// unlink, getcwd, chdir
# include <termios.h>     			// tcsetattr, tcgetattr
# include <curses.h>      			// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/ioctl.h>   			// ioctl
# include <getopt.h>      			// getopt
# include <limits.h>      			// PATH_MAX
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/time.h>
# include <time.h>
# include <string.h>
# include <stdint.h>

# ifdef FALSE
#  undef FALSE
# endif
# ifdef TRUE
#  undef TRUE
# endif

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_parse
{
	int		parts_num;
	int		*in_redir_num;
	char	***inputs_redirections;
	int		**inputs_tokens;
	int		*out_redir_num;
	char	***outputs_redirections;
	int		**outputs_tokens;
	char	***cmds;
	char 	**env;
	int 	fd_in;
	int 	fd_out;
	char	*pwd;
	int		redir;
}	t_parse;


void	jump_over_quote(char *cmd_line, int *i, int len);
char	*conv_tabs2spcs(char *cmd_line);
char	*delete_excess_spcs(char *cmd_line);
t_bool	check_pipe_redir(char *line);
t_bool	check_pipe_red_2(char *cmd_line);
int		*find_infiles_heredocs_num(char *cmd_line);
int		**find_ic_num(char *cmd_line);
int		*find_outfiles_appends_num(char *cmd_line);
int		**find_oc_num(char *cmd_line);
int		find_parts_num(char *cmd_line);
char	***malloc_file_names(int parts_num, int *each_part_redir_num, int **file_name_chars_num);
void	free_char_triple_pointer(char ***pointer);
char	***hold_input_file_names(char *cmd_line);
char	***hold_output_file_names(char *cmd_line);
t_bool	check_quotes(char *cmd_line);
void	remove_cmdline_quotes(char *cmd_line, char **ret, int char_num);
int		**tokenize_inputs(char *cmd_line);
int		**tokenize_outputs(char *cmd_line);
char	*conv_redir2spcs(char *cmd_line);
int		*find_cmds_num(char *cmd_line);
int		**find_cmds_chars_num(char *cmd_line);
char	***split_cmds(char *cmd_line);
t_bool	parse_shell(char *cmd_line, t_parse *parser);
int		count_size_without_redir(char *cmd_line);

// struct red
// {
// 	char *name;
// 	int flag;
// };


// typedef struct parser
// {
// 	struct *red;
// 	char **cmd;
// 	int redlen;
// };

// typedef s_struct1{
// 	int cmdnum;
// 	char **cmd;
// 	struct *s_struct2;
// } ;


#endif
