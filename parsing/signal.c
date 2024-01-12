/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:49:27 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/12 17:28:36 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include <signal.h>
/*
void	handle_sig(int sig, t_parse *parser)
{
	if (sig == SIGINT)
	{
		status = 130;
		if (user_input)
			ft_putstr_fd("\nminishell> ", 2);
		if (user_input)
			free(user_input);
		user_input = ft_strdup("\0");
	}
	else if (sig == SIGQUIT)
		write(2, "\b\b  \b\b", 6);
}

void	sig_init(t_parse *parser)
{
	if (signal(SIGINT, handle_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
	else if (signal(SIGQUIT, handle_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
}

void	handle_exec_sig(int sig, t_parse *parser)
{
	if (sig == SIGINT)
	{
		if (user_input)
			free(user_input);
		status = 130;
		quit = 1;
		write(2, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		status = 131;
		ft_putstr_fd("Exit (core dumped)\n", 2);
	}
}

void	sig_exec_init(void)
{
	if (signal(SIGINT, handle_exec_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
	else if (signal(SIGQUIT, handle_exec_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
}
*/