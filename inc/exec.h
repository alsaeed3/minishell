/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:51:06 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/16 20:54:20 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

# include "parser.h"

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

// int g_status;

#endif