/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:49:27 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/14 10:33:51 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
#include <signal.h>

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\b\b  \b\b\n", 6);
		write(2, "MINISHELL$ ", 11);
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
*/