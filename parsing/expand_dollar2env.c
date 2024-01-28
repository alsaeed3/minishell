/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar2env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:17:54 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/28 19:36:30 by alsaeed          ###   ########.fr       */
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
	while (i < len && ((cmd_line[i] >= 65 && cmd_line[i] <= 90) || (cmd_line[i] >= 97 && cmd_line[i] <= 122) || (cmd_line[i] >= 48 && cmd_line[i] <= 57)))
	{
		size++;
		i++;
	}
	return (size);		
}

static int expand_dollar_count(char *str, t_env *env_lst)
{
	t_bool	solo_quo_trigger;
	t_bool	duo_quo_trigger;
	t_bool	dollar_trigger;
	t_bool	redi_trigger;
	char	*env;
	int		len;
	int		i;
	int		j;
	size_t	exp_size;
	
	len = ft_strlen(str);
	solo_quo_trigger = FALSE;
	duo_quo_trigger = FALSE;
	dollar_trigger = FALSE;
	redi_trigger = FALSE;
	i = -1;
	j = 0;
	env = NULL;
	exp_size = 0;
	while (++i < len && str[i])
	{
		if (str[i] == '\'' && !solo_quo_trigger && !duo_quo_trigger)
		{
			++exp_size;
			i++;
			solo_quo_trigger = TRUE;
		}
		if (str[i] == '"' && !duo_quo_trigger && !solo_quo_trigger)
		{
			++exp_size;
			i++;
			duo_quo_trigger = TRUE;
		}
		if (i < len - 1 && ((str[i] == '<' && str[i + 1] != '<' && (i == 0 || str[i - 1] != '<')) || (str[i] == '>' && str[i + 1] != '>' && (i == 0 || str[i - 1] != '>'))) && !solo_quo_trigger && !duo_quo_trigger)
			redi_trigger = TRUE;
		else if (i < len - 1 && ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>')) && !solo_quo_trigger && !duo_quo_trigger)
			redi_trigger = TRUE;
		else if (i < len - 1 && ((str[i] == '<' && str[i + 1] != '<' && (i == 0 || str[i - 1] != '<')) || (str[i] == '>' && str[i + 1] != '>' && (i == 0 || str[i - 1] != '>'))) && (solo_quo_trigger || duo_quo_trigger))
			redi_trigger = FALSE;
		else if (i < len - 1 && ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>')) && (solo_quo_trigger || duo_quo_trigger))
			redi_trigger = FALSE;
		if (i < len - 2 && str[i] == '$' && !(str[i + 1] >= 65 && str[i + 1] <= 90) && !(str[i + 1] >= 97 && str[i + 1] <= 122) && !solo_quo_trigger)
			i += 2;
		else if (str[i] == '$' && ((str[i + 1] >= 65 && str[i + 1] <= 90) || (str[i + 1] >= 97 && str[i + 1] <= 122)) && !solo_quo_trigger && !redi_trigger)
			dollar_trigger = TRUE;
		if (dollar_trigger && ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)))
		{
				env = ft_calloc(find_env_size(str, i) + 1, sizeof(char));
				if (!env)
					return (0);
				j = 0;
				env[j++] = str[i];
				while(++i < len && ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || (str[i] >= 48 && str[i] <= 57)))
					env[j++] = str[i];
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
		if (str[i] == '\'' && solo_quo_trigger && !duo_quo_trigger)
		{
			exp_size++;
			i++;
			solo_quo_trigger = FALSE;
		}
		else if (str[i] == '"' && duo_quo_trigger && !solo_quo_trigger)
		{
			exp_size++;
			i++;
			duo_quo_trigger = FALSE;
		}
		if (str[i] == '$' && ((str[i + 1] >= 65 && str[i + 1] <= 90) || (str[i + 1] >= 97 && str[i + 1] <= 122)) && !dollar_trigger && !solo_quo_trigger && !redi_trigger)
			dollar_trigger = TRUE;
		else if (str[i] && (!dollar_trigger || str[i] != '$'))
			exp_size++;
	}
	return (exp_size);
}

char *expand_dollar_string(char *str, t_env *env_lst)
{
	t_bool	solo_quo_trigger;
	t_bool	duo_quo_trigger;
	t_bool	dollar_trigger;
	t_bool	redi_trigger;
	char	*env;
	int		len;
	int		i;
	int		j;
	int		k;
	int		exp_len;
	char	*ret;
	char	*env_ret;

	env_ret = NULL;
	exp_len = expand_dollar_count(str, env_lst);
	ret = ft_calloc(exp_len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	len = ft_strlen(str);
	redi_trigger = FALSE;
	solo_quo_trigger = FALSE;
	duo_quo_trigger = FALSE;
	dollar_trigger = FALSE;
	i = -1;
	j = 0;
	k = 0;
	while (++i < len && str[i])
	{
		if (str[i] == '\'' && !solo_quo_trigger && !duo_quo_trigger)
		{
			ret[j++] = str[i];
			i++;
			solo_quo_trigger = TRUE;
		}
		if (str[i] == '"' && !duo_quo_trigger && !solo_quo_trigger)
		{
			ret[j++] = str[i];
			i++;
			duo_quo_trigger = TRUE;
		}
		if (i < len - 1 && ((str[i] == '<' && str[i + 1] != '<' && (i == 0 || str[i - 1] != '<')) || (str[i] == '>' && str[i + 1] != '>' && (i == 0 || str[i - 1] != '>'))) && !solo_quo_trigger && !duo_quo_trigger)
			redi_trigger = TRUE;
		else if (i < len - 1 && ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>')) && !solo_quo_trigger && !duo_quo_trigger)
			redi_trigger = TRUE;
		else if (i < len - 1 && ((str[i] == '<' && str[i + 1] != '<' && (i == 0 || str[i - 1] != '<')) || (str[i] == '>' && str[i + 1] != '>' && (i == 0 || str[i - 1] != '>'))) && (solo_quo_trigger || duo_quo_trigger))
			redi_trigger = FALSE;
		else if (i < len - 1 && ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>')) && (solo_quo_trigger || duo_quo_trigger))
			redi_trigger = FALSE;
		if (i < len - 2 && str[i] == '$' && !(str[i + 1] >= 65 && str[i + 1] <= 90) && !(str[i + 1] >= 97 && str[i + 1] <= 122) && !solo_quo_trigger)
			i += 2;
		else if (str[i] == '$' && ((str[i + 1] >= 65 && str[i + 1] <= 90) || (str[i + 1] >= 97 && str[i + 1] <= 122)) && !solo_quo_trigger && !redi_trigger)
			dollar_trigger = TRUE;
		if (dollar_trigger && ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)))
		{
				env = ft_calloc(find_env_size(str, i) + 1, sizeof(char));
				if (!env)
					return (0);
				k = 0;
				env[k++] = str[i];
				while (++i < len && ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || (str[i] >= 48 && str[i] <= 57)))
					env[k++] = str[i];
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
		if (str[i] == '\'' && solo_quo_trigger && !duo_quo_trigger)
		{
			ret[j++] = str[i];
			i++;
			solo_quo_trigger = FALSE;
		}
		else if (str[i] == '"' && duo_quo_trigger && !solo_quo_trigger)
		{
			ret[j++] = str[i];
			i++;
			duo_quo_trigger = FALSE;
		}
		if (str[i] == '$' && ((str[i + 1] >= 65 && str[i + 1] <= 90) || (str[i + 1] >= 97 && str[i + 1] <= 122)) && !dollar_trigger && !solo_quo_trigger && !redi_trigger)
			dollar_trigger = TRUE;
		else if (str[i] && (!dollar_trigger || str[i] != '$'))
			ret[j++] = str[i];
	}
	ret[j] = '\0';
	return (ret);
}
