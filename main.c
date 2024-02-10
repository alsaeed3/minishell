/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/10 19:16:01 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/exec.h"

int	g_signal = 0;

int	main(int ac, char **av, char **env)
{
	t_main	main;

	(void)ac;
	(void)av;
	main = (t_main){0};
	main.parser = ft_calloc(1, sizeof(t_parse));
	if (!main.parser)
		return (1);
	if (data_init(&main.parser, env))
		return (1);
	while (1)
	{
		set_signals(&main.parser);
		if (data_reset(&main.parser))
			continue ;
		main.cmd_line = readline("minishell$ ");
		set_up_prompt(&main.parser, main.cmd_line);
		if (parse_shell(main.cmd_line, main.dup, &main.parser))
			continue ;
		exec_delegator(main.parser);
		free_parser(&main.parser);
	}
	free_util_1(&main.parser);
	return (0);
}
