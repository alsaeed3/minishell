/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:27:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/24 13:59:05 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_bool	parse_shell(char *cmd_line, char **original_envs, t_parse **parser)
{
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
	printf("expand_dollar_string {%s}\n", cmd_line);
	cmd_line = delete_excess_spcs(cmd_line);
	printf("delete_excess_spcs %s\n", cmd_line);
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
	(*parser)->in_redir_num = find_infiles_heredocs_num(cmd_line);
	(*parser)->inputs_redirections = hold_input_file_names(cmd_line);
	(*parser)->inputs_tokens = tokenize_inputs(cmd_line);
	printf("---------> before heredoc\n");
	for (int i = 0; i < (*parser)->parts_num; i++)
	{
		int j = -1;
		while ((*parser)->inputs_redirections[i][++j])
			printf("%s\n", (*parser)->inputs_redirections[i][j]);
	}
	printf("---------> before heredoc\n");
	find_heredocs_num(*parser);
	handle_heredoc(*parser);
	for (int ak = 0; ak < (*parser)->heredocs_num; ak++)
		printf("%s\n", (*parser)->heredoc_tmp_files[ak]);
	read_heredocs(*parser);
	(*parser)->out_redir_num = find_outfiles_appends_num(cmd_line);
	(*parser)->outputs_redirections = hold_output_file_names(cmd_line);
	(*parser)->outputs_tokens = tokenize_outputs(cmd_line);
	printf("before conv_redir2spcs {%s}\n", cmd_line);
	cmd_line = conv_redir2spcs(cmd_line);
	printf("conv_redir2spcs {%s}\n", cmd_line);
	cmd_line = delete_excess_spcs(cmd_line);
	printf("delete_excess_spcs {%s}\n", cmd_line);
	(*parser)->cmds = split_cmds(cmd_line);
	printf("cmds in parse_Shell\n");
	printf("\n");
	return (FALSE);
}
