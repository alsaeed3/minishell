/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:40:34 by habu-zua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/09 10:46:37 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/21 17:05:20 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	parent_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 99;
<<<<<<< HEAD
		// rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		// rl_on_new_line();
		if (waitpid(-1, NULL, WNOHANG) != -1)
			return ;
		// rl_redisplay();
=======
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		if (waitpid(-1, NULL, WNOHANG) != -1)
			return ;
		rl_redisplay();
>>>>>>> main
		return ;
	}
	else if (sig == SIGQUIT)
	{
<<<<<<< HEAD
		// rl_redisplay();
=======
		rl_redisplay();
>>>>>>> main
		return ;
	}
}

void	child_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
<<<<<<< HEAD
		// rl_replace_line("", 1);
		// rl_on_new_line();
=======
		rl_on_new_line();
>>>>>>> main
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
<<<<<<< HEAD
		ft_putstr_fd("\n", 1);
		// rl_replace_line("", 1);
		close(0);
		// rl_on_new_line();
=======
		close(0);
		ft_putstr_fd("\n", 1);
		g_signal = 1;
>>>>>>> main
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

<<<<<<< HEAD
void	set_signals(t_parse **parser)
=======
void	set_signals(t_parse **data)
>>>>>>> main
{
	signal(SIGINT, sig_switcher);
	signal(SIGQUIT, sig_switcher);
	if (g_signal != 1)
<<<<<<< HEAD
		(*parser)->exit_status = g_signal;
=======
		(*data)->exit_status = g_signal;
>>>>>>> main
	g_signal = 1;
}
