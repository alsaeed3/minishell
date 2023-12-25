/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:27:45 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/25 18:42:40 by alsaeed          ###   ########.fr       */
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

char	*conv_tabs2spcs(char *str);
bool	check_end_pipe(char *str);
bool	check_redir_end(char *str);
bool	check_pipe_red_2(char *str);
bool	check_pipe_redir(char *line);
int		*find_infiles_heredocs_num(char *str, int pipes_num);
void	find_ichar_num(char *cmd_line, int *char_num, int *reach);
void	find_ochar_num(char *cmd_line, int *char_num, int *reach);
int		**find_ic_num(char *cmd_line, int pipes_num, int *inputs_num);
int		**tokenize_inputs(char *cmd_line, int pipes_num, int *redir_num);
int		**tokenize_outputs(char *cmd_line, int pipes_num, int *redir_num);
int		*find_outfiles_appends_num(char *str, int pipes_num);
int		**find_oc_num(char *cmd_line, int pipes_num, int *inputs_num);
int		find_pipes_num(char *str);
bool	malloc_inputs(char ***inputs ,int pipes_num, int *each_part_inputs_num, int **file_name_chars_num);
void	free_inputs(char ***inputs ,int pipes_num, int *each_part_inputs_num, int **file_name_chars_num);
bool	check_quotes(char *str);
void	remove_str_quotes(char *str, char **ret, int char_num);

#endif
