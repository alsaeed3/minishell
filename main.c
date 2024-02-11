/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/11 13:49:52 by habu-zua         ###   ########.fr       */
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
	main.data = ft_calloc(1, sizeof(t_parse));
	if (!main.data)
		return (1);
	if (data_init(&main.data, env))
		return (1);
	while (1)
	{
		set_signals(&main.data);
		if (data_reset(&main.data))
			continue ;
		main.cmd_line = readline("minishell$ ");
		set_up_prompt(&main.data, main.cmd_line);
		if (parse_shell(main.cmd_line, main.dup, &main.data))
			continue ;
		exec_delegator(main.data);
		free_data(&main.data);
	}
	free_util_1(&main.data);
	return (0);
}
