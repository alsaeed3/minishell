/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:00:50 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/20 17:01:14 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	free_env(char **env)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = envlen(env);
	while (i < env_len)
		free(env[i++]);
	free(env);
}

int		envlen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	i++;
	return (i);
}

char	**dup_env(char **env)
{
	char	**data_env;
	int		env_size;
	int		i;

	if (!env)
		return (NULL);
	env_size = ft_array_size(env);
	data_env = ft_calloc(env_size + 10, sizeof(char *));
	if (!data_env)
		return (NULL);
	i = -1;
	while (++i < env_size && env[i])
		data_env[i] = ft_strdup(env[i]);
	if (data_env[i])
		data_env[++i] = NULL;
	else 
		data_env[i] = NULL;
	return (data_env);
}

void	handle_env(char **env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env[i])
	{
		str = ft_strnstr(env[i], "=", ft_strlen(env[i]));
		if (str)
		{
			j = 0;
			while (env[i][j])
			{
				write(1, &env[i][j], 1);
				j++;
			}
			ft_putchar('\n');
		}
		i++;
	}
	// g_status = 0;
}
