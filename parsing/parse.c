/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:27:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/10 19:15:47 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_bool	parse_shell(char *cmd_line, char *str, t_parse **data)
{
	str = ft_strdup(cmd_line);
	if (!str || !str[0])
		return (TRUE);
	str = conv_tabs2spcs(str);
	if (check_errors(str))
	{
		(*data)->exit_status = 258;
		return (TRUE);
	}
	str = delete_excess_spcs(str);
	(*data)->envs_lst = get_envs_lst((*data)->env);
	str = expand_dollar_string(str, (*data)->envs_lst);
	(*data)->parts_num = find_parts_num(str);
	(*data)->in_rdr_num = find_rdr_num(str, '<', (*data));
	(*data)->inputs_redirections = hold_rdr_names(str, '<', (*data));
	// ft_putchar_fd('{', 2);
	// ft_putstr_fd((*data)->inputs_redirections[0][0], 2);
	// ft_putchar_fd('}', 2);
	// ft_putchar_fd('\n', 2);
	(*data)->inputs_tokens = tokenize_redir(str, (*data), '<');
	find_heredocs_num((*data));
	handle_heredoc((*data));
	(*data)->out_rdr_num = find_rdr_num(str, '>', (*data));
	(*data)->outputs_redirections = hold_rdr_names(str, '>', (*data));
	// ft_putchar_fd('{', 2);
	// ft_putstr_fd((*data)->outputs_redirections[0][0], 2);
	// ft_putchar_fd('}', 2);
	// ft_putchar_fd('\n', 2);
	(*data)->outputs_tokens = tokenize_redir(str, (*data), '>');
	str = conv_redir2spcs(str);
	// ft_putchar_fd('{', 2);
	// ft_putstr_fd(str, 2);
	// ft_putchar_fd('}', 2);
	// ft_putchar_fd('\n', 2);
	str = delete_excess_spcs(str);
	(*data)->cmds = split_cmds(str);
	return (FALSE);
}

t_bool	check_errors(char *str)
{
	if (check_quotes(str) || check_pipe_red_2(str) || check_pipe_redir(str))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		free_set_null(str);
		return (TRUE);
	}
	return (FALSE);
}
