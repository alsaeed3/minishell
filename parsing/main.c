/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/07 21:08:49 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int main(void)
{
	while (1)
	{
		char	*input = readline("$ ");
		char	*indup = ft_strdup(input);
		free (input);
		indup = delete_excess_spcs(indup);
		// printf("d_e_s: %s\n", indup);
		indup = conv_redir2spcs(indup);
		printf("conv_red2spc: %s\n", indup);
		// indup = delete_excess_spcs(indup);
		int *cmds_num = find_cmds_num(indup);
		int parts_num = find_parts_num(indup);
		int **cmds_chars_num = find_cmds_chars_num(indup);
		// printf("parts_num: %d\n", parts_num);
		// printf("%s\n", indup);
		for(int i = 0; i < parts_num; i++)
		{
			for (int j = 0; j < cmds_num[i]; j++)
				printf("part: %d, cmd_num: %d, chars_num: %d\n", i, j, cmds_chars_num[i][j]);
		}
		free (indup);
	}
	return (0);
}

/* to check outputs files names' extraction */
// int main(void)
// {
// 	while (1)
// 	{
// 		char	*input = readline("$ ");
// 		char	*outdup = ft_strdup(input);
// 		outdup = conv_tabs2spcs(outdup);
// 		outdup = delete_excess_spcs(outdup);
// 		if (check_pipe_redir(outdup) || check_pipe_red_2(outdup) || check_quotes(outdup))
// 		{
// 			printf("Error\n");
// 			continue ;
// 		}
// 		char	***outputs_names = hold_output_file_names(outdup);
// 		for (int i = 0; outputs_names[i]; i++)
// 		{
// 			for (int j = 0; outputs_names[i][j]; j++)
// 			{
// 				printf("part:{%d}, order:{%d}, out_redir:{%s}\n", i, j, outputs_names[i][j]);
// 			}
// 		}
// 		free_char_triple_pointer(outputs_names);
// 	}
// 	return (0);
// }

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

/* to check inputs files names' extraction */
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
// 		int		parts_num = find_parts_num(indup);
// 		int		*ihn = find_infiles_heredocs_num(indup, parts_num);
// 		int		**icn = find_ic_num(indup, parts_num, ihn);
// 		char	***inputs_names = hold_input_file_names(indup, parts_num, ihn, icn);
// 		for (int i = 0; i < parts_num; i++)
// 		{
// 			for (int j = 0; j < ihn[i]; j++)
// 			{
// 				printf("part:{%d}, order:{%d}, redir:{%s}\n", i, j, inputs_names[i][j]);
// 			}
// 		}
// 		free_inputs(inputs_names, parts_num, ihn);
// 	}
// 	return (0);
// }
