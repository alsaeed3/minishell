/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:48:44 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/14 17:41:23 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/exec.h"

static int		cd_minus(t_parse *data)
{
	if (var_index("OLDPWD=", data) < 0 ||
	chdir((strchr(data->env[var_index("OLDPWD=", data)], '=') + 1)) == -1)
		return (0);
	change_pwd(data, NULL);
	return (1);
}

static int		cd_alone(t_parse *data)
{
	if (var_index("HOME=", data) < 0 ||
	chdir((strchr(data->env[var_index("HOME=", data)], '=') + 1)) == -1)
		return (0);
	change_pwd(data, NULL);
	return (1);
}

static int		cd_path(char **args, t_parse *data)
{
	if (chdir(args[1]) == -1)
		return (0);
	change_pwd(data, args[1]);
	return (1);
}

void	handle_cd(char **args, t_parse *data)
{
	printf("handle_cd\n");
	if (args[1] && args[2])
		return (error_sentence("cd: too many arguments\n", 1));
	else if (!args[1])
	{
		if (!cd_alone(data))
			return (error_sentence("cd: HOME: is undefined\n", 1));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (!cd_minus(data))
			return (error_sentence("cd: OLDPWD is undefined\n", 1));
	}
	else
	{
		if (!cd_path(args, data))
			return (error_sentence("cd: no such file or directory\n", 1));
	}
	g_status = 0;
}
