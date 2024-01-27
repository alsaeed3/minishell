/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:27:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/27 12:58:57 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_bool	parse_shell(char *cmd_line, char **original_envs, t_parse **parser)
{
	t_var	*var;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (TRUE);
	if (!cmd_line || ft_strcmp(cmd_line, "\n") == 0)
		return (TRUE);
	cmd_line = conv_tabs2spcs(cmd_line);
	if (check_quotes(cmd_line))
	{
		printf("Quote Error\n");
		return (TRUE);
	}
	(*parser)->envs_lst = get_envs_lst(original_envs);
	cmd_line = expand_dollar_string(cmd_line, (*parser)->envs_lst);
	// printf("expand_dollar_string {%s}\n", cmd_line);
	cmd_line = delete_excess_spcs(cmd_line);
	// printf("delete_excess_spcs %s\n", cmd_line);
	if (check_pipe_redir(cmd_line))
	{
		printf("Pipe-Redir Error\n");
		return (TRUE);
	}
	if (check_pipe_red_2(cmd_line))
	{
		printf("Pipe-Redir-2 Error\n");
		return (TRUE);
	}
	(*parser)->parts_num = find_parts_num(cmd_line);
	(*parser)->in_rdr_num = find_rdr_num(cmd_line, '<', (*parser));
	(*parser)->inputs_redirections = hold_rdr_names(cmd_line, '<', (*parser));
	(*parser)->inputs_tokens = tokenize_inputs(cmd_line, (*parser));
	// printf("---------> before heredoc\n");
	// for (int i = 0; i < (*parser)->parts_num; i++)
	// {
	// 	int j = -1;
	// 	if ((*parser)->inputs_redirections && (*parser)->inputs_redirections[i])
	// 	{
	// 		while ((*parser)->inputs_redirections[i][++j])
	// 			printf("%s\n", (*parser)->inputs_redirections[i][j]);
	// 	}
	// }
	// printf("---------> before heredoc\n");
	find_heredocs_num(*parser);
	handle_heredoc(*parser);
	// for (int ak = 0; ak < (*parser)->heredocs_num; ak++)
	// 	printf("%s\n", (*parser)->heredoc_tmp_files[ak]);
	// read_heredocs(*parser);
	(*parser)->out_rdr_num = find_rdr_num(cmd_line, '>', (*parser));
	(*parser)->outputs_redirections = hold_rdr_names(cmd_line, '>', (*parser));
	(*parser)->outputs_tokens = tokenize_outputs(cmd_line, (*parser));
	// printf("before conv_redir2spcs {%s}\n", cmd_line);
	cmd_line = conv_redir2spcs(cmd_line);
	// printf("conv_redir2spcs {%s}\n", cmd_line);
	cmd_line = delete_excess_spcs(cmd_line);
	// printf("delete_excess_spcs {%s}\n", cmd_line);
	(*parser)->cmds = split_cmds(cmd_line);
	// printf("cmds in parse_Shell\n");
	// printf("\n");
	return (FALSE);
}
