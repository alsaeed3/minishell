/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:05:46 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/11 23:28:20 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	handle_echo(char **args, t_data *data)
{
	int i;
	int n_flag;

	i = 1;
	n_flag = 0;
	data->status = 0;
	while (args[i] && !ft_strcmp(args[i], "-n") && i++)
		n_flag = 1;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
}
