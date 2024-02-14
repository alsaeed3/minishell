/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:54:53 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/14 13:32:30 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	change_env_pwd(t_parse *data)
{
	char	*pwd;

	data->pwd = getcwd(NULL, 0);
	if (var_index("PWD", data) >= 0)
	{
		pwd = ft_strjoin("PWD=", data->pwd);
		replace_var(pwd, data, var_index(pwd, data));
		free_set_null(pwd);
	}
	else
	{
		pwd = ft_strjoin("PWD=", data->pwd);
		data->env = export_env(data->env, pwd);
		free_set_null(pwd);
	}
}

void	change_env_oldpwd(t_parse *data)
{
	char	*pwd;
	char	*oldpwd;

	if (var_index("OLDPWD", data) >= 0)
	{
		pwd = ft_strjoin("PWD=", data->pwd);
		oldpwd = ft_strjoin("OLD", pwd);
		replace_var(oldpwd, data, var_index("OLDPWD=", data));
		free_set_null(oldpwd);
		free_set_null(pwd);
	}
	else
		data->env = export_env(data->env, "OLDPWD");
	free_set_null(data->pwd);
}

int	change_pwd(t_parse *data, char *input)
{
	char	*pwd;
	char	*cwd;

	if (var_index("PWD", data) < 0)
		return (0);
	cwd = getcwd(NULL, 0);
	if (!cwd && input && ft_strcmp(".", input) == 0)
	{
		ft_putstr_fd("Error retrieving current directory", 2);
		pwd = data->pwd;
		data->pwd = ft_strjoin(pwd, "/.");
		free_set_null(pwd);
	}
	if (cwd)
	{
		change_env_oldpwd(data);
		change_env_pwd(data);
	}
	free_set_null(cwd);
	return (1);
}
