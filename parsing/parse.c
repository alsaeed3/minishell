/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:27:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/09 14:14:55 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_bool	parse_shell(char *cmd_line, t_parse *parser)
{
	cmd_line = conv_tabs2spcs(cmd_line);
	cmd_line = delete_excess_spcs(cmd_line);
	if (check_quotes(cmd_line) || check_pipe_redir(cmd_line) || check_pipe_red_2(cmd_line))
	{
		printf("Error\n");
		return (TRUE);
	}
	parser->parts_num = find_parts_num(cmd_line);
	parser->in_redir_num = find_infiles_heredocs_num(cmd_line);
	parser->inputs_redirections = hold_input_file_names(cmd_line);
	parser->inputs_tokens = tokenize_inputs(cmd_line);
	parser->out_redir_num = find_outfiles_appends_num(cmd_line);
	parser->outputs_redirections = hold_output_file_names(cmd_line);
	parser->outputs_tokens = tokenize_outputs(cmd_line);
	cmd_line = conv_redir2spcs(cmd_line);
	cmd_line = delete_excess_spcs(cmd_line);
	parser->cmds = split_cmds(cmd_line);
	return (FALSE);
}
