/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/28 18:32:36 by habu-zua         ###   ########.fr       */
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
	char	*cmd_line;

	data_init(&parser, env);
	while (1)
	{
		set_signals(parser);
		data_reset(&parser);
		
		cmd_line = readline("MINISHELL$ ");
		if (g_signal == 99)
			parser->exit_status = 1;
		g_signal = 1;
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


//ls -la | wc| cat <<w >v