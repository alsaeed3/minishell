/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:40:34 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/27 17:42:40 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"
extern int  g_signal;

void	handle_parent_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		// rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 99;
		return ;
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
}

void	handle_child_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		// rl_replace_line("", 1);
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

void	exit_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		// rl_replace_line("", 1);
		close(0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 130;
	}
}

void	is_parent_child_sig(int sig)
{
	if (g_signal == 3)
		handle_child_sig(sig);
	else if (g_signal == 2)
		exit_heredoc(sig);
	else
		handle_parent_sig(sig);
}


void set_signals(t_parse *parser)
{
		signal(SIGINT, is_parent_child_sig);
		signal(SIGQUIT, is_parent_child_sig);
		if (g_signal != 1)
			parser->exit_status = g_signal;
		g_signal = 1;
	
}