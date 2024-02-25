/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:00:50 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/20 15:44:30 by alsaeed          ###   ########.fr       */
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
		free_set_null((void **)&env[i++]);
	free_set_null((void **)&env);
}

int	envlen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (++i);
}

char	**dup_env(char **env)
{
	char	**data_env;
	int		i;

	i = 0;
	data_env = malloc(sizeof(char *) * envlen(env));
	if (!data_env)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		data_env[i] = ft_strdup(env[i]);
		i++;
	}
	data_env[i] = 0;
	return (data_env);
}

void	handle_env(char **env)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	if (!env)
		return ;
	while (++i < envlen(env) && env[i])
	{
		if (ft_strlen((ft_strchr(env[i], '=') + 1)) == 0)
			continue ;
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
	}
}
