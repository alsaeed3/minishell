/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:27:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/21 15:43:24 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

t_bool	parse_shell(char *cmd_line, char *str, t_parse **data)
{
	str = ft_strdup(cmd_line);
	if (!str)
		return (TRUE);
	if (!str[0])
		return (free_set_null((void **)&str), TRUE);
	str = conv_tabs2spcs(str);
	str = delete_excess_spcs(str);
	if (check_errors(str))
		return ((*data)->exit_status = 258, TRUE);
	(*data)->envs_lst = get_envs_lst((*data)->env);
	str = expand_dollar_string(str, (*data)->envs_lst);
	str = expand_dollar_sign(str, *data);
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

t_bool	check_errors(char *str)
{
	if (check_quotes(str) || check_pipe_red_2(str) || check_pipe_redir(str))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		free_set_null((void **)&str);
		return (TRUE);
	}
	return (FALSE);
}
