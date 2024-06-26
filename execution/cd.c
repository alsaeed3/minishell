/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:48:44 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/20 15:44:47 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static int	cd_alone(t_parse *data)
{
	if (var_index("HOME=", data) < 0 \
	|| chdir((strchr(data->env[var_index("HOME=", data)], '=') + 1)) == -1)
	{
		ft_error("cd: HOME: is undefined");
		data->exit_status = 1;
		return (1);
	}
	change_pwd(data, NULL);
	return (0);
}

static int	cd_minus(t_parse *data)
{
	if (var_index("OLDPWD=", data) < 0 \
		|| chdir((strchr(data->env[var_index("OLDPWD=", data)], '=') + 1))
		== -1)
	{
		ft_error("cd: OLDPWD is undefined");
		data->exit_status = 1;
		return (1);
	}
	change_pwd(data, NULL);
	return (0);
}

static int	cd_path(char **args, t_parse *data)
{
	char	*tmp;

	if (args[1][0] == '~')
	{
		if (var_index("HOME=", data) < 0)
		{
			ft_error("cd: HOME: is undefined");
			data->exit_status = 1;
			return (1);
		}
		tmp = args[1];
		args[1] = ft_strjoin((strchr(data->env[var_index("HOME=", data)], \
		'=') + 1), (args[1] + 1));
		free (tmp);
	}
	if (chdir(args[1]) == -1)
	{
		ft_error("cd: No such file or directory");
		data->exit_status = 1;
		return (1);
	}
	change_pwd(data, args[1]);
	return (0);
}

int	handle_cd(char **args, t_parse *data)
{
	int	ret;

	ret = 0;
	if (!args[1])
		ret = cd_alone(data);
	else if (ft_strcmp(args[1], "-") == 0)
		ret = cd_minus(data);
	else
		ret = cd_path(args, data);
	return (ret);
}
