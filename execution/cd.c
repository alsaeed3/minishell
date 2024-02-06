/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:48:44 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/31 00:42:47 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static void	cd_alone(t_parse *data)
{
	if (var_index("HOME=", data) < 0
		|| chdir((strchr(data->env[var_index("HOME=", data)], '=') + 1)) == -1)
		ft_error("cd: HOME: is undefined\n");
	data->exit_status = 1;
	change_pwd(data, NULL);
}
static void	cd_minus(t_parse *data)
{
	if (var_index("OLDPWD=", data) < 0
		|| chdir((strchr(data->env[var_index("OLDPWD=", data)], '=') + 1))
		== -1)
	{
		ft_error("cd: OLDPWD is undefined\n");
		data->exit_status = 1;
		// printf("worng path");
	}
	change_pwd(data, NULL);
}

static void	cd_path(char **args, t_parse *data)
{
	if (chdir(args[1]) == -1)
	{
		ft_error("cd: no such file or directory\n");
		data->exit_status = 1;
	}
	change_pwd(data, args[1]);
}

void	handle_cd(char **args, t_parse *data)
{
	printf("handle_cd\n");
	if (args[1] && args[2])
	{
		ft_error("cd: too many arguments\n");
		data->exit_status = 1;
		return ;
	}
	else if (!args[1])
		cd_alone(data);
	else if (ft_strcmp(args[1], "-") == 0)
		cd_minus(data);
	else
		cd_path(args, data);
}
