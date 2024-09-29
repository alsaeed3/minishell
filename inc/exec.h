/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:51:06 by habu-zua          #+#    #+#             */
/*   Updated: 2024/09/29 10:33:14 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "./data.h"
# define FORKED_CHILD 0

typedef struct s_pipe
{
	pid_t	*pid;
	int		i;
	int		j;
	int		(*pipe_fds)[2];
	int		ret;
}	t_pipe;

typedef struct s_rdr
{
	struct stat	path_stat;
	int			i;
	int			len;
	int			size;
	char		*direc;
	char		*filename;
	int			fd;
	int			flags;
	t_bool		dir;
}	t_rdr;

void		exec_delegator(t_parse **data);
int			handle_cd(char **args, t_parse *data);
int			var_index(char *name, t_parse *data);
void		replace_var(char *new_var, t_parse *data, int index);
char		**export_env(char **old_env, char *export);
void		export_alone(t_parse *data);
int			handle_export(char **inputs, t_parse *data, int i);
void		change_env_pwd(t_parse *data);
void		change_env_oldpwd(t_parse *data);
int			change_pwd(t_parse *data, char *input);
void		handle_exit(char **args, t_parse *data, t_pipe *pipes, int mode);
void		free_env(char **env);
int			envlen(char **env);
char		**dup_env(char **env);
void		handle_env(char **env);

int			check_export(char *str);
int			print_export(char **env);
void		handle_echo(t_parse *data, int x);
int			handle_unset(char **inputs, t_parse *data);
void		handle_pwd(t_parse *data);

t_bool		data_init(t_parse **data, char **env);
t_bool		data_reset(t_parse **data);

int			redirect_from(t_parse *data);
int			redirect_to(t_parse *data);
int			redirect_to_pipe(t_parse *data, t_pipe *pipes);
int			redirect_from_pipe(t_parse *data, t_pipe *pipes);

char		**gen_paths(int index, t_parse *data, char *input);
int			check_exec_path(char **inputs, t_parse *data);
int			check_exec(char **inputs, t_parse *data);

int			handle_pipe(t_parse *data);
int			handle_single(char **inputs, t_parse *data);

void		close_fds(t_parse *data);

int			choose_action(char **cmd, t_parse *data);
int			handle_exec(char **inputs, t_parse *data);
int			handle_exec_pipe(char **inputs, t_parse *data, t_pipe *pipes);
int			execute_2(char **inputs, t_parse *data);
int			execute(char **inputs, t_parse *data);

void		free_exit(t_parse *data, int status, int mode);

void		set_signals(t_parse **data);
void		sig_switcher(int sig);

void		ft_error(char *str);

void		free_close_fd(t_parse *data, int mode, int status, t_pipe *pipes);
void		print_message(char *cmd, char *message);
char		*get_file_name(t_parse *data, int x);

void		expand_dolar_sign(char **inputs, t_parse *data);
void		handle_single_pipe(char **inputs, t_parse *data, t_pipe *pipes);

int			execute_2_pipe(char **inputs, t_parse *data);
void		choose_action_pipe(char **cmd, t_parse *data, t_pipe *pipes, \
			int fd);
int			handle_unset(char **inputs, t_parse *data);
int			execute_pipe(char **inputs, t_parse *data);
int			execute_2_pipe(char **inputs, t_parse *data);
void		close_new_fd(t_parse *data);
int			ft_strcmp1(char *s1, char *s2);

void		init_rdr(char *str, t_rdr *rdr);
t_bool		get_direc(t_rdr *rdr, char *str);
t_bool		check_dir_out(char *str);
t_bool		is_filename(char *filename);
char		*get_file_name(t_parse *data, int x);

int			check_file_dir(char **filename);
int			check_exec_file(char **inputs, t_parse *data);

#endif