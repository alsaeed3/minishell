/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2-print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/05 17:34:27 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "./inc/exec.h"

// int g_signal = 0;
// /* Test the whole parsing in int main */
// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	t_parse	*parser;
// 	char	*cmd_line;
// 	parser = NULL;
// 	while (1)
// 	{
// 		parser = ft_calloc(1, sizeof(t_parse));
// 		printf("---------------------------------------------\n");
// 		cmd_line = readline("MINISHELL$ ");
// 		add_history(cmd_line);
// 		char	*dup = ft_strdup(cmd_line);
		
// 		printf("\n");
// 		if (parse_shell(dup, env, &parser))
// 			continue ;
// 		// free (dup);
// 		int j;
// 		printf("parts_num = %d\n", parser->parts_num);
// 		printf("\n");
// 		printf("---------------------------------------------\n");
// 		printf("#       inputs_redirection_file_names:      #\n");
// 		int	i = -1;
// 		if (parser->inputs_redirections)
// 		{
// 			while(parser->inputs_redirections[++i])
// 			{
// 				j = -1;
// 				while (parser->inputs_redirections[i][++j])
// 					printf("-------->part:[%d], order:[%d] = {%s}\n", i, j, parser->inputs_redirections[i][j]);			
// 			}
// 		}
// 		printf("\n");
// 		printf("---------------------------------------------\n");
// 		printf("#                inputs_tokens:             #\n");
// 		i = -1;
// 		if (parser->in_rdr_num)
// 		{
// 			while (++i < parser->parts_num)
// 			{
// 				j = -1;
// 				while (++j < parser->in_rdr_num[i])
// 					printf("-------->part:[%d], order:[%d] = { %d }\n", i, j, parser->inputs_tokens[i][j]);
// 			}
// 		}
// 		printf("\n");
// 		printf("---------------------------------------------\n");
// 		printf("#      outputs_redirection_file_names:      #\n");
// 		i = -1;
// 		if (parser->outputs_redirections)
// 		{
// 			while(parser->outputs_redirections[++i])
// 			{
// 				j = -1;
// 				while (parser->outputs_redirections[i][++j])
// 					printf("-------->part:[%d], order:[%d] = {%s}\n", i, j, parser->outputs_redirections[i][j]);			
// 			}
// 		}
// 		printf("\n");
// 		printf("---------------------------------------------\n");
// 		printf("#               outputs_tokens:             #\n");
// 		i = -1;
// 		while (++i < parser->parts_num)
// 		{
// 			j = -1;
// 			while (++j < parser->out_rdr_num[i])
// 				printf("-------->part:[%d], order:[%d] = { %d }\n", i, j, parser->outputs_tokens[i][j]);
// 		}
// 		printf("\n");
// 		printf("---------------------------------------------\n");
// 		printf("#                   cmds:                   #\n");
// 		i = -1;
// 		while(parser->cmds[++i])
// 		{
// 			j = -1;
// 			while (parser->cmds[i][++j])
// 				printf("-------->part:[%d], order:[%d] = {%s}\n", i, j, parser->cmds[i][j]);			
// 		}
// 		printf("\n");
// 		free(cmd_line);
// 		cmd_line = NULL;
// 		// printf("---------------------------------------------\n");
// 		// printf("#                   envs:                   #\n");
// 		// t_env *curr = parser->envs_lst;
// 		// while (curr != NULL)
// 		// {
// 		// 	printf("-------->key   = {%s}\n", curr->key);
// 		// 	printf("-------->info  = {%s}\n", curr->info);
// 		// 	curr = curr->next;
// 		// }
// 	}
// 	return (0);
// }

// void	ft_free_lst(t_env **stack)
// {
// 	t_env	*curr;
// 	t_env	*next;

// 	curr = *stack;
// 	if (*stack != NULL)
// 	{
// 		while (curr->next != NULL)
// 		{
// 			if (curr->info)
// 				free (curr->info);
// 			if (curr->key)
// 				free (curr->key);
// 			next = curr->next;
// 			free (curr);
// 			curr = next;
// 		}
// 		if (curr != NULL)
// 		{
// 			if (curr->info)
// 				free (curr->info);
// 			if (curr->key)
// 				free (curr->key);
// 			free (curr);
// 		}
// 	}
// }

// void	ft_free_intarr(int **int_arr, int parts)
// {
// 	int	i;

// 	i = -1;
// 	if (!int_arr)
// 		return ;
// 	while (++i < parts)
// 	{
// 		if (int_arr[i])
// 			free (int_arr[i]);
// 	}
// 	if (int_arr)
// 		free (int_arr);
// }

// void	free_parser(t_parse **parse)
// {
// 	free_char_triple_pointer((*parse)->inputs_redirections);
// 	free_char_triple_pointer((*parse)->cmds);
// 	ft_free_array((*parse)->heredoc_tmp_files);
// 	ft_free_lst(&(*parse)->envs_lst);
// 	ft_free_intarr((*parse)->inputs_tokens, (*parse)->parts_num);
// 	ft_free_intarr((*parse)->outputs_tokens, (*parse)->parts_num);
// 	free ((*parse)->in_rdr_num);
// 	free ((*parse)->out_rdr_num);
// }

//ls -la | wc| cat <<w >v

/* To check quote */
// int main(void)
// {
// 	while (1)
// 	{
// 		char *input = readline("$ ");
// 		char *dup = ft_strdup(input);
// 		free (input);
// 		if (check_quotes(dup))
// 		{
// 			printf("Error\n");
// 			continue;
// 		}
// 		free (dup);
// 	}
// }

/* To test splitting commands from the commandline into char*** variable */
// int main(void)
// {
// 	while (1)
// 	{
// 		char	*input = readline("$ ");
// 		char	*indup = ft_strdup(input);
// 		free (input);
// 		indup = delete_excess_spcs(indup);
// 		indup = conv_redir2spcs(indup);
// 		char ***cmds = split_cmds(indup);
// 		int j;
// 		int i = -1;
// 		while (cmds[++i])
// 		{
// 			j = -1;
// 			while(cmds[i][++j])
// 				printf("part: %d, cmd: %d: %s\n", i, j, cmds[i][j]);
// 		}
// 		free (indup);
// 	}
// 	return (0);
// }

/* To test finding each command characters number on each part */
// int main(void)
// {
// 	while (1)
// 	{
// 		char	*input = readline("$ ");
// 		char	*indup = ft_strdup(input);
// 		free (input);
// 		indup = delete_excess_spcs(indup);
// 		// printf("d_e_s: %s\n", indup);
// 		indup = conv_redir2spcs(indup);
// 		printf("conv_red2spc: %s\n", indup);
// 		// indup = delete_excess_spcs(indup);
// 		int *cmds_num = find_cmds_num(indup);
// 		int parts_num = find_parts_num(indup);
// 		int **cmds_chars_num = find_cmds_chars_num(indup);
// 		// printf("parts_num: %d\n", parts_num);
// 		// printf("%s\n", indup);
// 		for(int i = 0; i < parts_num; i++)
// 		{
// 			for (int j = 0; j < cmds_num[i]; j++)
// 				printf("part: %d, cmd_num: %d, chars_num: %d\n", i, j, cmds_chars_num[i][j]);
// 		}
// 		free (indup);
// 	}
// 	return (0);
// }

/* To test finding commands number on each part function */
// int main(void)
// {
// 	while (1)
// 	{
// 		char	*input = readline("$ ");
// 		char	*indup = ft_strdup(input);
// 		free (input);
// 		indup = delete_excess_spcs(indup);
// 		indup = conv_redir2spcs(indup);
// 		int *cmds_num = find_cmds_num(indup);
// 		int parts_num = find_parts_num(indup);
// 		printf("parts_num: %d\n", parts_num);
// 		printf("%s\n", indup);
// 		for(int i = 0; i < parts_num; i++)
// 			printf("part:[%d] --> cmds_num = %d\n", i, cmds_num[i]);
// 		free (indup);
// 	}
// 	return (0);
// }

/* to check outputs files names' extraction */
// int main(void)
// {
// 	while (1)
// 	{
// 		char	*input = readline("$ ");
// 		char *indup = ft_strdup(input);
// 		indup = conv_tabs2spcs(indup);
// 		indup = delete_excess_spcs(indup);
// 		if (check_pipe_redir(indup) || check_pipe_red_2(indup) || check_quotes(indup))
// 		{
// 			printf("Error\n");
// 			continue ;
// 		}
// 		char	***outputs_names = hold_output_file_names(indup);
// 		int i = -1;
// 		int j;
// 		while(outputs_names[++i])
// 		{
// 			j = -1;
// 			while (outputs_names[i][++j])
// 				printf("part:{%d}, order:{%d}, redir:{%s}\n", i, j, outputs_names[i][j]);			
// 		}
// 		free_char_triple_pointer(outputs_names);
// 	}
// 	return (0);
// }

/* To try convertings redirections and their file names to spaces */
// int main(void)
// {
// 	while (1)
// 	{
// 		char	*input = readline("$ ");
// 		char	*indup = ft_strdup(input);
// 		indup = conv_redir2spcs(indup);
// 		printf("%s\n", indup);
// 		free (input);
// 		free (indup);
// 	}
// 	return (0);
// }

/* to check inputs redirections files names' extraction */
// int main(void)
// {
// 	while (1)
// 	{
// 		char	*input = readline("$ ");
// 		char *indup = ft_strdup(input);
// 		indup = conv_tabs2spcs(indup);
// 		indup = delete_excess_spcs(indup);
// 		if (check_pipe_redir(indup) || check_pipe_red_2(indup) || check_quotes(indup))
// 		{
// 			printf("Error\n");
// 			continue ;
// 		}
// 		char	***inputs_names = hold_input_file_names(indup);
// 		int i = -1;
// 		int j;
// 		while(inputs_names[++i])
// 		{
// 			j = -1;
// 			while (inputs_names[i][++j])
// 				printf("part:{%d}, order:{%d}, redir:{%s}\n", i, j, inputs_names[i][j]);			
// 		}
// 		free_char_triple_pointer(inputs_names);
// 	}
// 	return (0);
// }


