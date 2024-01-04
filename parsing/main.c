/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/04 21:38:06 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int main(void)
{
	while (1)
	{
		char	*input = readline("$ ");
		char *indup = ft_strdup(input);
		indup = conv_tabs2spcs(indup);
		if (check_pipe_redir(indup) || check_pipe_red_2(indup) || check_quotes(indup))
		{
			printf("Error\n");
			continue ;
		}
		indup = delete_excess_spcs(indup);
		int		parts_num = find_parts_num(indup);
		int		*ihn = find_infiles_heredocs_num(indup, parts_num);
		int		**icn = find_ic_num(indup, parts_num, ihn);
		char	***inputs_names = hold_input_file_names(indup, parts_num, ihn, icn);
		for (int i = 0; i < parts_num; i++)
		{
			for (int j = 0; j < ihn[i]; j++)
			{
				printf("part: %d, order: %d, redir: %s\n", i, j, inputs_names[i][j]);
			}
		}
		free_inputs(inputs_names, parts_num, ihn);
	}
	return (0);
}

// int main(void)
// {
// 	int	i = -1;
// 	char *cmd_line = readline("$> ");
// 	char *ret;
	
// 	if (check_quotes(cmd_line))
// 	{
// 		printf("Error\nquotes\n");
// 		return (1);
// 	}
// 	ret = conv_tabs2spcs(cmd_line);
// 	ret = delete_excess_spcs(ret);
// 	if (check_pipe_redir(ret))
// 	{
// 		printf("Error\ncheck_pipe_redir\n");
// 		return (1);
// 	}
// 	else if (check_pipe_red_2(ret))
// 	{
// 		printf("Error\ncheck_pipe_red_2(\n");
// 		return (1);
// 	}
	
// }
