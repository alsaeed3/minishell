/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:03:01 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/26 18:53:11 by habu-zua         ###   ########.fr       */
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:03:01 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/21 17:00:29 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

int	check_export(char *str)
{
	int	i;

	i = 0;
<<<<<<< HEAD
	if (ft_isdigit(str[i]))
=======
	if (ft_isdigit(str[i]) || str[i] == '=' || str[i] == '+')
>>>>>>> main
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

int	print_export(char **env)
{
<<<<<<< HEAD
	int	i;
	int	j;
	int	equal;

	i = -1;
	while (env[++i])
	{
		equal = 1;
		j = 0;
		ft_putstr("declare -x ");
		while (env[i][j])
		{
			if (env[i][j] == '\\' || env[i][j] == '$' ||
			env[i][j] == '\"')
				write(1, "\\", 1);
			write(1, &env[i][j], 1);
			if (env[i][j] == '=' && equal-- == 1)
				write(1, "\"", 1);
			j++;
		}
		if (equal != 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
	return (1);
=======
	t_var	var;

	var.i = -1;
	if (!env || !*env)
		return (0);
	while (env[++var.i])
	{
		var.k = 1;
		var.j = 0;
		ft_putstr("declare -x ");
		while (env[var.i][var.j])
		{
			if (env[var.i][var.j] == '\\' || env[var.i][var.j] == '$' ||
			env[var.i][var.j] == '\"')
				write(1, "\\", 1);
			write(1, &env[var.i][var.j], 1);
			if (env[var.i][var.j] == '=' && var.k-- == 1)
				write(1, "\"", 1);
			var.j++;
		}
		if (var.k != 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
	return (0);
>>>>>>> main
}
