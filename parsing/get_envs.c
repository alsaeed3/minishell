/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:28:28 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/16 14:48:32 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static t_env	*ft_env_last(t_env *head)
{
	while (head->next != NULL)
		head = head->next;
	return (head);
}

static int		get_key_size(char *env)
{
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	return (i);		
}

static char		*get_env_key(char *env)
{
	char	*key;
	int		i;

	i = 0;
	key = ft_calloc(get_key_size(env) + 1, sizeof(char));
	while (env[i] != '=')
	{
		key[i] = env[i];	
		i++;
	}
	key[i] = '\0';
	return (key);		
}

static int	get_info_size(char *env)
{
	int		i;
	int		j;

	i = 0;
	while (env[i] != '=')
		i++;
	j = 0;
	while (env[i] != '\0')
	{
		j++;
		i++;
	}
	return (j);	
}

static char		*get_env_info(char *env)
{
	char	*info;
	int		i;
	int		j;

	i = 0;
	info = ft_calloc(get_info_size(env) + 1, sizeof(char));
	while (env[i] != '=')
		i++;
	i++;
	j = 0;
	while (env[i] != '\0')
		info[j++] = env[i++];
	info[j] = '\0';
	return (info);	
}

static t_env	*add_env(t_env *head, char *env)
{
	t_env	*last_env;
	t_env	*new_env;

	if (head == NULL)
	{
		new_env = (t_env *)ft_calloc(1, sizeof(t_env));
		new_env->key = get_env_key(env);
		new_env->info = get_env_info(env);
		new_env->next = NULL;
		head = new_env;
		return (head);
	}
	if (head != NULL)
	{
		last_env = ft_env_last(head);
		new_env = (t_env *)ft_calloc(1, sizeof(t_env));
		if (!new_env)
			return (NULL);
		new_env->key = get_env_key(env);
		new_env->info = get_env_info(env);;
		new_env->next = NULL;
		last_env->next = new_env;
	}
	return (head);
}


t_env	*get_envs(char **original_envs)
{
	t_env	*envs;
	int		i;

	i = 0;
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