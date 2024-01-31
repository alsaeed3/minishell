/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/31 15:18:00 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/exec.h"

int  g_signal = 0; 

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_parse	*parser;
	char	*cmd_line;

	while (1)
	{
		parser = ft_calloc(1, sizeof(t_parse));
		if (!parser)
			continue ;
		if (data_init(&parser, env))
			continue ;
		set_signals(&parser);
		// signal(SIGINT, sig_switcher);
		// signal(SIGQUIT, sig_switcher);
		// if (g_signal != 1)
		// 	parser->exit_status = g_signal;
		// g_signal = 1;
		// data_reset(&parser);
		cmd_line = readline("minishell$ ");
		if (g_signal == 99)
			parser->exit_status = 1;
		g_signal = 1;
		if (cmd_line == NULL)
		{
			printf("exit\n");
			rl_clear_history();
			exit(0);
		}
		add_history(cmd_line);
		if (g_signal == 99)
			parser->exit_status = 1;
     	char	*dup = ft_strdup(cmd_line);
		if (parse_shell(dup, env, &parser))
			continue ;
		free (dup);
		// exec_delegator(parser);
		free_parser(&parser);
	}
	return (0);
}

void	ft_free_lst(t_env **stack)
{
	t_env	*curr;
	t_env	*next;

	curr = *stack;
	if (*stack != NULL)
	{
		while (curr->next != NULL)
		{
			next = curr->next;
			free (curr);
			curr = next;
		}
		if (curr != NULL)
			free (curr);
	}
}

void	ft_free_intarr(int **int_arr, int parts)
{
	int	i;

	i = -1;
	if (!int_arr)
		return ;
	while (++i < parts)
	{
		if (int_arr[i])
			free (int_arr[i]);
	}
	if (int_arr)
		free (int_arr);
}

void	free_parser(t_parse **parse)
{
	free_char_triple_pointer((*parse)->inputs_redirections);
	free_char_triple_pointer((*parse)->cmds);
	ft_free_array((*parse)->env);
	ft_free_array((*parse)->heredoc_tmp_files);
	free((*parse)->pwd);
	ft_free_lst(&(*parse)->envs_lst);
	ft_free_intarr((*parse)->inputs_tokens, (*parse)->parts_num);
	ft_free_intarr((*parse)->outputs_tokens, (*parse)->parts_num);
	free(*parse);
	*parse = NULL;
}

//ls -la | wc| cat <<w >v