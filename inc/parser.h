/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:27:45 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/06 05:32:34 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

void	jump_over_quote(char *cmd_line, int *i, int len);
char	*conv_tabs2spcs(char *str);
char	*delete_excess_spcs(char *cmd_line);
t_bool	check_pipe_redir(char *line);
t_bool	check_pipe_red_2(char *str);
int		*find_infiles_heredocs_num(char *str, int parts_num);
int		**find_ic_num(char *cmd_line, int parts_num, int *inputs_num);
int		*find_outfiles_appends_num(char *str, int parts_num);
int		**find_oc_num(char *cmd_line, int parts_num, int *outputs_num);
int		find_parts_num(char *str);
char	***malloc_inputs(int parts_num, int *each_part_inputs_num, int **file_name_chars_num);
char	***malloc_outputs(int parts_num, int *each_part_outputs_num, int **file_name_chars_num);
void	free_char_triple_pointer(char ***pointer);
char	***hold_input_file_names(char *cmd_line, int parts_num, int *inputs_num, int ** ic_num);
char	***hold_output_file_names(char *cmd_line);
t_bool	check_quotes(char *str);
void	remove_str_quotes(char *str, char **ret, int char_num);
int		**tokenize_inputs(char *cmd_line, int parts_num, int *redir_num);
int		**tokenize_outputs(char *cmd_line, int parts_num, int *redir_num);
char	*conv_redir2spcs(char *cmd_line);

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
