/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:48:44 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/21 12:08:18 by habu-zua         ###   ########.fr       */
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:48:44 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/20 15:44:47 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

<<<<<<< HEAD
static void	cd_minus(t_parse *data);
static void	cd_alone(t_parse *data);
static void	cd_path(char **args, t_parse *data);

void	handle_cd(char **args, t_parse *data)
{
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
	if (var_index("HOME=", data) < 0 ||
	chdir((strchr(data->env[var_index("HOME=", data)], '=') + 1)) == -1)
		error_sentence("cd: HOME: is undefined\n", 1);
	change_pwd(data, NULL);
}

static void	cd_minus(t_parse *data)
{
	if (var_index("OLDPWD=", data) < 0 ||
	chdir((strchr(data->env[var_index("OLDPWD=", data)], '=') + 1)) == -1)
	{
		error_sentence("cd: OLDPWD is undefined\n", 1);
		printf("worng path");
	}
	change_pwd(data, NULL);
}

static void	cd_path(char **args, t_parse *data)
{
	if (chdir(args[1]) == -1)
		error_sentence("cd: no such file or directory\n", 1);
	change_pwd(data, args[1]);
=======
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
>>>>>>> main
}
