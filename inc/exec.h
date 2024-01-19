/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:51:06 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/19 23:23:11 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

# include "parser.h"
# define FORKED_CHILD 0


void    exec_delegator(t_parse *parser);
void    ft_free(char **cmd);
char    *ft_getpath(char *cmd, char *envpath);
void	handle_cd(char **args, t_parse *data);
int		var_index(char *name, t_parse *data);
void	replace_var(char *new_var, t_parse *data, int index);
char	**export_env(char **old_env, char *export);
void	export_alone(t_parse *data);
void	handle_export(char **inputs, t_parse *data);
void	change_env_pwd(t_parse *data);
void	change_env_oldpwd(t_parse *data);
int		change_pwd(t_parse *data, char *input);
void	error_sentence(char *str, int status);
void	handle_exit(char **inputs, t_parse *data);
void	free_env(char **env);
int		envlen(char **env);
char	**dup_env(char **env);
void	handle_env(char **env);

int		check_export(char *str);
int		print_export(char **env);
void	handle_echo(char **args);
void	handle_unset(char **inputs, t_parse *data);
void	handle_pwd(t_parse *data);

void	data_init(t_parse *data, char **env);

void    redirect_from(t_parse *data, int x);
void    redirect_to(t_parse *data, int x);

char	**gen_paths(int index, t_parse *data, char *input);
int		check_exec_path(char **inputs, t_parse *data);
int		check_exec(char **inputs, t_parse *data);


int     handle_pipe(t_parse *parser);
int		handle_single(char **inputs, t_parse *data, int piped, int x);
void	exit_pipe(t_parse *data);

void	close_fds(t_parse *data);

void	choose_action(char **inpts,t_parse *data);
void	handle_exec(char **inputs, t_parse *data);
int		execute_2(char **inputs, t_parse *data);
int		execute(char **inputs, t_parse *data);
#endif