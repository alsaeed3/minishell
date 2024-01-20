/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:25:23 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/20 15:04:10 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/exec.h"

void	check_n_flag(char *args, int *i, int *n_flag);
void	handle_echo(char **args)
{
	int i;
	int n_flag;

	i = 1;
	n_flag = 0;
	while (args[i] && !ft_strcmp(args[i], "-n"))
	{
		remove_cmdline_quotes(args[i], &args[i], ft_strlen(args[i]));
		printf("args[i] = %s\n", args[i]);
		check_n_flag(args[i], &i, &n_flag);
		i++;
	}
	printf("n_flag = %d\n", n_flag);
	printf("i = %d\n", i);
	printf("args[i] = %s\n", args[i]);
	
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

void	check_n_flag(char *args, int *i, int *n_flag)
{
	printf("check_n_flag\n");
	unsigned long j;

	j = 1;
	printf("args length = %lu\n", ft_strlen(args));
	while(j < ft_strlen(args))
	{
		printf("args[j] = %c\n", args[j]);
		while(args[j]  && args[j] == 'n')
			j++;
		printf("j = %lu\n", j);
		if(args[j] == '\0')
		{
			*n_flag = 1;
			(*i)++;
		}
		j++;
	}
}
