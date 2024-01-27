/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:48:44 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/27 12:22:20 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static void	cd_minus(t_parse *data);
static void	cd_alone(t_parse *data);
static void	cd_path(char **args, t_parse *data);

void	handle_cd(char **args, t_parse *data)
{
	printf("handle_cd\n");
	if (args[1] && args[2])
		return (error_sentence("cd: too many arguments\n", 1));
	else if (!args[1])
		cd_alone(data);
	else if (ft_strcmp(args[1], "-") == 0)
		cd_minus(data);
	else
		cd_path(args, data);
}

static void	cd_alone(t_parse *data)
{
	if (var_index("HOME=", data) < 0
		|| chdir((strchr(data->env[var_index("HOME=", data)], '=') + 1)) == -1)
		error_sentence("cd: HOME: is undefined\n", 1);
	change_pwd(data, NULL);
}

static void	cd_minus(t_parse *data)
{
	if (var_index("OLDPWD=", data) < 0
		|| chdir((strchr(data->env[var_index("OLDPWD=", data)], '=') + 1))
		== -1)
	{
		error_sentence("cd: OLDPWD is undefined\n", 1);
		// printf("worng path");
	}
	change_pwd(data, NULL);
}

static void	cd_path(char **args, t_parse *data)
{
	if (chdir(args[1]) == -1)
		error_sentence("cd: no such file or directory\n", 1);
	change_pwd(data, args[1]);
}
