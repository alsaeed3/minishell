/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:54:53 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/19 12:12:49 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/exec.h"

t_env	*search_env_key(char *key, t_env *envs)
{
	t_env	*curr;

	curr = envs;
	while (curr != NULL)
	{
		if (!(ft_strcmp(key, curr->key)))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	change_env_pwd(t_parse *data)
{
	t_env	*pwd_node;
	t_env	*last_env;

	data->pwd = getcwd(NULL, 0);
	if (ft_getenv("PWD", data->envs_lst))
	{
		pwd_node = search_env_key("PWD", data->envs_lst);
		free (pwd_node->info);
		pwd_node->info = ft_strdup(data->pwd);
	}
	else
	{
		last_env = ft_env_last(data->envs_lst);
		pwd_node = (t_env *)ft_calloc(1, sizeof(t_env));
		if (!pwd_node)
			return ;
		pwd_node->key = "PWD";
		pwd_node->info = ft_strdup(data->pwd);
		pwd_node->next = NULL;
		last_env->next = pwd_node;
	}
}

void	change_env_oldpwd(t_parse *data)
{
	t_env	*oldpwd_node;
	t_env	*last_env;

	if (var_index("OLDPWD", data) >= 0)
	{
		oldpwd_node = search_env_key("OLDPWD", data->envs_lst);
		free (oldpwd_node->info);
		oldpwd_node->info = ft_strdup(data->pwd);
	}
	else
	{
		last_env = ft_env_last(data->envs_lst);
		oldpwd_node = (t_env *)ft_calloc(1, sizeof(t_env));
		if (!oldpwd_node)
			return ;
		oldpwd_node->key = "OLDPWD";
		oldpwd_node->info = ft_strdup(data->pwd);
		oldpwd_node->next = NULL;
		last_env->next = oldpwd_node;
	}
	free(data->pwd);
}

int		change_pwd(t_parse *data, char *input)
{
	char	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd && input && ft_strcmp(".", input) == 0)
	{
		ft_putstr_fd("Error retrieving current directory\n", 2);
		pwd = data->pwd;
		data->pwd = ft_strjoin(pwd, "/.");
		free(pwd);
	}
	if (cwd)
	{
		change_env_oldpwd(data);
		change_env_pwd(data);
	}
	free(cwd);
	return (1);
}
