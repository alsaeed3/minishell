/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/02 14:49:16 by alsaeed          ###   ########.fr       */
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/21 16:35:07 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "./inc/exec.h"

<<<<<<< HEAD
int	g_signal = 0; 

int main(int ac, char **av, char **env)
{
	t_parse	*parser;
	char	*cmd_line;
	char	*dup;
	(void)ac;
	(void)av;

	parser = NULL;
	dup = NULL;
	parser = ft_calloc(1, sizeof(t_parse));
	if (!parser)
		return (0);
	if (data_init(&parser, env))
		return (0);
	while (1)
	{
		set_signals(&parser);
		// signal(SIGINT, sig_switcher);
		// signal(SIGQUIT, sig_switcher);
		// if (g_signal != 1)
		// 	parser->exit_status = g_signal;
		// g_signal = 1;
		if (data_reset(&parser))
			continue ;
		cmd_line = readline("minishell$ ");
		if (g_signal == 99)
			parser->exit_status = 1;
		g_signal = 1;
		if (cmd_line == NULL)
		{
			printf("exit\n");
			// rl_clear_history();
			exit(0);
		}
		add_history(cmd_line);
		if (g_signal == 99)
			parser->exit_status = 1;
     	dup = ft_strdup(cmd_line);
		if (parse_shell(dup, env, &parser))
			continue ;
		// if (dup)
		// 	free (dup);
		exec_delegator(parser);
		free_parser(&parser);
	}
	free(parser->pwd);
	ft_free_array(parser->env);
	free(parser);
	parser = NULL;
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
			if (curr->info)
				free (curr->info);
			if (curr->key)
				free (curr->key);
			next = curr->next;
			free (curr);
			curr = next;
		}
		if (curr != NULL)
		{
			if (curr->info)
				free (curr->info);
			if (curr->key)
				free (curr->key);
			free (curr);
		}
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
	ft_free_array((*parse)->heredoc_tmp_files);
	ft_free_lst(&(*parse)->envs_lst);
	ft_free_intarr((*parse)->inputs_tokens, (*parse)->parts_num);
	ft_free_intarr((*parse)->outputs_tokens, (*parse)->parts_num);
	free ((*parse)->in_rdr_num);
	free ((*parse)->out_rdr_num);
}

//ls -la | wc| cat <<w >v
=======
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
		exec_delegator(&main.data);
		free_data(&main.data);
	}
	free_util_1(&main.data);
	return (0);
}
>>>>>>> main
