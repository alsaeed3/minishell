/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:28:28 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/19 12:12:15 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_env	*ft_env_last(t_env *head)
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

t_env	*add_env(t_env *head, char *env, t_env_size *envs_size)
{
	t_env	*last_env;
	t_env	*new_env;

	if (head == NULL)
	{
		new_env = (t_env *)ft_calloc(1, sizeof(t_env));
		if (!new_env)
			return (NULL);
		new_env->full_env = ft_strdup(env);
		new_env->key = get_env_key(env);
		new_env->info = get_env_info(env);
		new_env->env_size = envs_size;
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
		new_env->full_env = ft_strdup(env);
		new_env->key = get_env_key(env);
		new_env->info = get_env_info(env);
		new_env->env_size = envs_size;
		new_env->next = NULL;
		last_env->next = new_env;
	}
	return (head);
}

t_env	*unset_env(t_env *head, char *env_key)
{
	t_env	*curr;
	t_env	*tmp;
	t_env	*prev;

	curr = head;
	tmp = NULL;
	prev = NULL;
	while (curr != NULL)
	{
		if (ft_strcmp(env_key, curr->key) == 0)
		{
			if (!prev) // it is head node
			{
				tmp = head;
				head = head->next;
				head->env_size->envs_size--;
			}
			else // it is non-head node
			{
				tmp = curr;
				prev->next = curr->next;
				head->env_size->envs_size--;
			}
			free(tmp->full_env);
			free(tmp->key);
			free(tmp->info);
			free(tmp);
			break;
		}
		prev = curr;
		curr = curr->next;
	}
	return (head);
}

t_env	*get_envs_lst(char **original_envs)
{
	t_env		*envs;
	t_env_size	*env_size;
	int		i;
	int		envs_size;

	i = 0;
	envs = NULL;
	envs_size = ft_array_size(original_envs);
	env_size = ft_calloc(1, sizeof(t_env_size));
	env_size->envs_size = envs_size;
	while (original_envs[i])
	{
		envs = add_env(envs, original_envs[i], env_size);
		i++;
	}
	return (envs);
}

char	**get_envs_array(t_env *env_lst)
{
	char	**envs_array;
	t_env	*curr;
	int		i;

	curr = env_lst;
	envs_array = ft_calloc(env_lst->env_size->envs_size + 1, sizeof(char *));
	if (!envs_array)
		return (NULL);
	i = 0;
	while (curr != NULL)
	{
		envs_array[i] = ft_strdup(curr->full_env);
		i++;
		curr = curr->next;
	}
	envs_array[i] = NULL;
	return (envs_array);
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