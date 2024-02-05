/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:27:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/05 21:31:04 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_bool	prepare_parse(char *str)
{
	if (check_quotes(str))
	{
		printf("Quote Error\n");
		return (TRUE);
	}
	if (check_pipe_redir(str))
	{
		printf("Pipe-Redir Error\n");
		return (TRUE);
	}
	if (check_pipe_red_2(str))
	{
		printf("Pipe-Redir-2 Error\n");
		return (TRUE);
	}
	return (FALSE);
}

t_bool	parse_shell(char *str, char **original_envs, t_parse **data)
{
	(void)original_envs;
	if (!str || !str[0])
		return (TRUE);
	str = conv_tabs2spcs(str);
	if (prepare_parse(str))
		return (TRUE);
	str = delete_excess_spcs(str);
	(*data)->envs_lst = get_envs_lst((*data)->env);
	str = expand_dollar_string(str, (*data)->envs_lst);
	(*data)->parts_num = find_parts_num(str);
	(*data)->in_rdr_num = find_rdr_num(str, '<', (*data));
	(*data)->inputs_redirections = hold_rdr_names(str, '<', (*data));
	(*data)->inputs_tokens = tokenize_redir(str, (*data), '<');
	find_heredocs_num((*data));
	handle_heredoc((*data));
	(*data)->out_rdr_num = find_rdr_num(str, '>', (*data));
	(*data)->outputs_redirections = hold_rdr_names(str, '>', (*data));
	(*data)->outputs_tokens = tokenize_redir(str, (*data), '>');
	str = conv_redir2spcs(str);
	str = delete_excess_spcs(str);
	(*data)->cmds = split_cmds(str);
	return (FALSE);
}
