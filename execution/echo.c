/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:25:23 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/21 11:58:34 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:25:23 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/14 20:55:43 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

>>>>>>> main
#include "../inc/exec.h"

static int	is_n_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

<<<<<<< HEAD
void	handle_echo(char **args)
{
	printf("handle_echo\n");
	int i;
	int n_flag;

	i = 1;
	n_flag = 1;
	while (args[i] && is_n_flag(args[i]))
=======
void	handle_echo(t_parse *data, int x)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 1;
	while (data->cmds[x][i] && is_n_flag(data->cmds[x][i]))
>>>>>>> main
	{
		n_flag = 0;
		i++;
	}
<<<<<<< HEAD
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
=======
	while (data->cmds[x][i])
	{
		write(1, data->cmds[x][i], ft_strlen(data->cmds[x][i]));
		if (data->cmds[x][i + 1])
>>>>>>> main
			write(1, " ", 1);
		i++;
	}
	if (n_flag)
		write(1, "\n", 1);
}
