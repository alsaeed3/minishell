/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:27:45 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/12 14:39:00 by alsaeed          ###   ########.fr       */
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

#endif
