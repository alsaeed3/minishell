/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:40:34 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/21 16:04:50 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	parent_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 99;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		if (waitpid(-1, NULL, WNOHANG) != -1)
			return ;
		rl_redisplay();
		return ;
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
}

void	child_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		g_signal = 130;
		return ;
	}
	else if (sig == SIGQUIT)
	{
		g_signal = 131;
		printf("Quit: 3\n");
		return ;
	}
}

void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		ft_putstr_fd("\n", 1);
		g_signal = 1;
	}
}

void	sig_switcher(int sig)
{
	if (g_signal == 3)
		child_sig(sig);
	else if (g_signal == 2)
		heredoc_sig(sig);
	else
		parent_sig(sig);
}

void	set_signals(t_parse **data)
{
	signal(SIGINT, sig_switcher);
	signal(SIGQUIT, sig_switcher);
	if (g_signal != 1)
		(*data)->exit_status = g_signal;
	g_signal = 1;
}
