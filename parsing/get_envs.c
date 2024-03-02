/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:28:28 by alsaeed           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/13 13:56:00 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/14 18:14:17 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static char	*get_env_key(char *env)
{
	char	*key;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = ft_calloc(i + 1, sizeof(char));
	if (!key)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static char	*get_env_info(char *env)
{
<<<<<<< HEAD
	char	*info;
	size_t	i;
	size_t	j;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && env[i] != '=')
		i++;
	j = 0;
	while (env[i] && env[i] != '\0')
=======
	t_inf	inf;

	inf = (t_inf){0};
	if (!env)
		return (NULL);
	while (env[inf.i] && env[inf.i] != '=')
		inf.i++;
	inf.j = 0;
	while (env[inf.i] && env[inf.i] != '\0')
>>>>>>> main
	{
		inf.j++;
		inf.i++;
	}
<<<<<<< HEAD
	info = ft_calloc(j + 1, sizeof(char));
	if (!info)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	j = 0;
	while (i < ft_strlen(env) && env[i] != '\0')
		info[j++] = env[i++];
	info[j] = '\0';
	return (info);
=======
	inf.info = ft_calloc(inf.j + 1, sizeof(char));
	if (!inf.info)
		return (NULL);
	inf.i = 0;
	while (env[inf.i] && env[inf.i] != '=')
		inf.i++;
	inf.i++;
	inf.j = 0;
	while (inf.i < (int)ft_strlen(env) && env[inf.i] != '\0')
		inf.info[inf.j++] = env[inf.i++];
	inf.info[inf.j] = '\0';
	return (inf.info);
>>>>>>> main
}

t_env	*add_env(t_env *head, char *env)
{
	t_env	*last_env;
	t_env	*new_env;
<<<<<<< HEAD
	
	if (!env)
		return (head);
	if (head == NULL)
=======

	if (env && head == NULL)
>>>>>>> main
	{
		new_env = (t_env *)ft_calloc(1, sizeof(t_env));
		new_env->key = get_env_key(env);
		new_env->info = get_env_info(env);
		new_env->next = NULL;
		head = new_env;
		return (head);
	}
	if (env && head != NULL)
	{
		last_env = ft_env_last(head);
		new_env = (t_env *)ft_calloc(1, sizeof(t_env));
		if (!new_env)
			return (head);
		new_env->key = get_env_key(env);
		new_env->info = get_env_info(env);
		new_env->next = NULL;
		last_env->next = new_env;
	}
	return (head);
}

t_env	*get_envs_lst(char **original_envs)
{
	t_env	*envs;
	int		i;

	i = 0;
	if (original_envs == NULL)
		return (NULL);
	envs = NULL;
	while (original_envs[i])
	{
		envs = add_env(envs, original_envs[i]);
		i++;
	}
	return (envs);
}

char	*ft_getenv(char *key, t_env *envs)
{
	while (envs != NULL)
	{
		if (!ft_strcmp(key, envs->key))
			return (envs->info);
		envs = envs->next;
	}
	return (NULL);
}
