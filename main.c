/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/27 17:45:34 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/exec.h"
int  g_signal = 0; 

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_parse	*parser;
	parser = ft_calloc(1, sizeof(t_parse));
	data_init(&parser, env);
	char	*cmd_line;

	while (1)
	{
		set_signals(parser);
		cmd_line = readline("MINISHELL$ ");
		if (!cmd_line)
			exit(0);
		add_history(cmd_line);
		if (g_signal == 99)
			parser->exit_status = 1;
     	char	*dup = ft_strdup(cmd_line);
		if (parse_shell(dup, env, &parser))
			continue ;
		free (dup);
		exec_delegator(parser);
	}
	return (0);
}
