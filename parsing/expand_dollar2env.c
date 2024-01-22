/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar2env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:17:54 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/22 08:44:27 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static int	find_env_size(char *cmd_line, int i)
{
	int	len;
	int	size;

	len = ft_strlen(cmd_line);
	size = 0;
	if (cmd_line[i] == '$')
		i++;
	while (i < len && ((cmd_line[i] >= 65 && cmd_line[i] <= 90) || (cmd_line[i] >= 97 && cmd_line[i] <= 122)))
	{
		size++;
		i++;
	}
	return (size);		
}

static int expand_dollar_count(char *cmd_line, t_env *env_lst)
{
	t_bool	solo_quo_trigger;
	t_bool	duo_quo_trigger;
	t_bool	dollar_trigger;
	char	*env;
	int		len;
	int		i;
	int		j;
	size_t	exp_size;
	
	len = ft_strlen(cmd_line);
	solo_quo_trigger = FALSE;
	duo_quo_trigger = FALSE;
	dollar_trigger = FALSE;
	i = -1;
	j = 0;
	env = NULL;
	exp_size = 0;
	while (++i < len && cmd_line[i])
	{
		if (cmd_line[i] == '\'' && !solo_quo_trigger && !duo_quo_trigger)
		{
			++exp_size;
			i++;
			solo_quo_trigger = TRUE;
		}
		if (cmd_line[i] == '"' && !duo_quo_trigger && !solo_quo_trigger)
		{
			++exp_size;
			i++;
			duo_quo_trigger = TRUE;
		}
		if (i < len - 2 && cmd_line[i] == '$' && !(cmd_line[i + 1] >= 65 && cmd_line[i + 1] <= 90) && !(cmd_line[i + 1] >= 97 && cmd_line[i + 1] <= 122) && !solo_quo_trigger)
			i += 2;
		else if (cmd_line[i] == '$' && ((cmd_line[i + 1] >= 65 && cmd_line[i + 1] <= 90) || (cmd_line[i + 1] >= 97 && cmd_line[i + 1] <= 122)) && !solo_quo_trigger)
			dollar_trigger = TRUE;
		if (dollar_trigger && ((cmd_line[i] >= 65 && cmd_line[i] <= 90) || (cmd_line[i] >= 97 && cmd_line[i] <= 122)))
		{
				env = ft_calloc(find_env_size(cmd_line, i) + 1, sizeof(char));
				if (!env)
					return (0);
				j = 0;
				env[j++] = cmd_line[i];
				while(++i < len && ((cmd_line[i] >= 65 && cmd_line[i] <= 90) || (cmd_line[i] >= 97 && cmd_line[i] <= 122) || (cmd_line[i] >= 48 && cmd_line[i] <= 57)))
					env[j++] = cmd_line[i];
				env[j] = '\0';
				dollar_trigger = FALSE;
				if (ft_getenv(env, env_lst))
					exp_size += ft_strlen(ft_getenv(env ,env_lst));
				if (env)
				{
					free (env);
					env = NULL;
				}
		}
		if (cmd_line[i] == '\'' && solo_quo_trigger && !duo_quo_trigger)
		{
			exp_size++;
			i++;
			solo_quo_trigger = FALSE;
		}
		else if (cmd_line[i] == '"' && duo_quo_trigger && !solo_quo_trigger)
		{
			exp_size++;
			i++;
			duo_quo_trigger = FALSE;
		}
		if (cmd_line[i] == '$' && ((cmd_line[i + 1] >= 65 && cmd_line[i + 1] <= 90) || (cmd_line[i + 1] >= 97 && cmd_line[i + 1] <= 122)) && !dollar_trigger && !solo_quo_trigger)
			dollar_trigger = TRUE;
		else if (cmd_line[i] && (!dollar_trigger || cmd_line[i] != '$'))
			exp_size++;
	}
	return (exp_size);
}

char *expand_dollar_string(char *cmd_line, t_env *env_lst)
{
	t_bool	solo_quo_trigger;
	t_bool	duo_quo_trigger;
	t_bool	dollar_trigger;
	char	*env;
	int		len;
	int		i;
	int		j;
	int		k;
	int		exp_len;
	char	*ret;
	char	*env_ret;

	env_ret = NULL;
	exp_len = expand_dollar_count(cmd_line, env_lst);
	ret = ft_calloc(exp_len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	len = ft_strlen(cmd_line);
	solo_quo_trigger = FALSE;
	duo_quo_trigger = FALSE;
	dollar_trigger = FALSE;
	i = -1;
	j = 0;
	k = 0;
	while (++i < len && cmd_line[i])
	{
		if (cmd_line[i] == '\'' && !solo_quo_trigger && !duo_quo_trigger)
		{
			ret[j++] = cmd_line[i];
			i++;
			solo_quo_trigger = TRUE;
		}
		if (cmd_line[i] == '"' && !duo_quo_trigger && !solo_quo_trigger)
		{
			ret[j++] = cmd_line[i];
			i++;
			duo_quo_trigger = TRUE;
		}
		if (i < len - 2 && cmd_line[i] == '$' && !(cmd_line[i + 1] >= 65 && cmd_line[i + 1] <= 90) && !(cmd_line[i + 1] >= 97 && cmd_line[i + 1] <= 122) && !solo_quo_trigger)
			i += 2;
		else if (cmd_line[i] == '$' && ((cmd_line[i + 1] >= 65 && cmd_line[i + 1] <= 90) || (cmd_line[i + 1] >= 97 && cmd_line[i + 1] <= 122)) && !solo_quo_trigger)
			dollar_trigger = TRUE;
		if (dollar_trigger && ((cmd_line[i] >= 65 && cmd_line[i] <= 90) || (cmd_line[i] >= 97 && cmd_line[i] <= 122)))
		{
				env = ft_calloc(find_env_size(cmd_line, i) + 1, sizeof(char));
				if (!env)
					return (0);
				k = 0;
				env[k++] = cmd_line[i];
				while(++i < len && ((cmd_line[i] >= 65 && cmd_line[i] <= 90) || (cmd_line[i] >= 97 && cmd_line[i] <= 122) || (cmd_line[i] >= 48 && cmd_line[i] <= 57)))
					env[k++] = cmd_line[i];
				env[k] = '\0';
				dollar_trigger = FALSE;
				if (ft_getenv(env, env_lst))
				{
					k = 0;
					env_ret = ft_getenv(env, env_lst);
					while(j < exp_len && env_ret[k])
						ret[j++] = env_ret[k++];
				}
				if (env)
				{
					free (env);
					env = NULL;
				}
		}
		if (cmd_line[i] == '\'' && solo_quo_trigger && !duo_quo_trigger)
		{
			ret[j++] = cmd_line[i];
			i++;
			solo_quo_trigger = FALSE;
		}
		else if (cmd_line[i] == '"' && duo_quo_trigger && !solo_quo_trigger)
		{
			ret[j++] = cmd_line[i];
			i++;
			duo_quo_trigger = FALSE;
		}
		if (cmd_line[i] == '$' && ((cmd_line[i + 1] >= 65 && cmd_line[i + 1] <= 90) || (cmd_line[i + 1] >= 97 && cmd_line[i + 1] <= 122)) && !dollar_trigger && !solo_quo_trigger)
			dollar_trigger = TRUE;
		else if (cmd_line[i] && (!dollar_trigger || cmd_line[i] != '$'))
			ret[j++] = cmd_line[i];
	}
	ret[j] = '\0';
	return (ret);
}
