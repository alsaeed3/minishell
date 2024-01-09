/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/09 14:17:43 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

/* Test the whole parsing in int main */
int main(void)
{
	t_parse	parser;
	while (1)
	{
		char	*cmd_line = readline("$ ");
		char	*dup = ft_strdup(cmd_line);
		free (cmd_line);
		if (parse_shell(dup, &parser))
			continue ;
		free (dup);
		int j;
		printf("parts_num = %d\n", parser.parts_num);
		printf("---------------------------------------------\n");
		printf("---------------------------------------------\n");
		printf("#       inputs_redirection_file_names:      #\n");
		int	i = -1;
		while(parser.inputs_redirections[++i])
		{
			j = -1;
			while (parser.inputs_redirections[i][++j])
				printf("      part:{%d}, order:{%d}, in_redir:{%s}\n", i, j, parser.inputs_redirections[i][j]);			
		}
		printf("---------------------------------------------\n");
		printf("---------------------------------------------\n");
		printf("#                inputs_tokens:             #\n");
		i = -1;
		while (++i < parser.parts_num)
		{
			j = -1;
			while (++j < parser.in_redir_num[i])
				printf("      part: %d, in_token: %d = %d\n", i, j, parser.inputs_tokens[i][j]);
		}
		printf("---------------------------------------------\n");
		printf("---------------------------------------------\n");
		printf("#      outputs_redirection_file_names:      #\n");
		i = -1;
		while(parser.outputs_redirections[++i])
		{
			j = -1;
			while (parser.outputs_redirections[i][++j])
				printf("      part:{%d}, order:{%d}, out_redir:{%s}\n", i, j, parser.outputs_redirections[i][j]);			
		}
		printf("---------------------------------------------\n");
		printf("---------------------------------------------\n");
		printf("#               outputs_tokens:             #\n");
		i = -1;
		while (++i < parser.parts_num)
		{
			j = -1;
			while (++j < parser.out_redir_num[i])
				printf("      part: %d, out_token: %d = %d\n", i, j, parser.outputs_tokens[i][j]);
		}
		printf("---------------------------------------------\n");
		printf("---------------------------------------------\n");
		printf("#                   cmds:                   #\n");
		i = -1;
		while(parser.cmds[++i])
		{
			j = -1;
			while (parser.cmds[i][++j])
				printf("         part:{%d}, order:{%d}, cmd:{%s}\n", i, j, parser.cmds[i][j]);			
		}
		// free_char_triple_pointer(inputs_names);
	}
	return (0);
}

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
