/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:03:01 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/14 21:09:48 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

int	check_export(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
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
}
