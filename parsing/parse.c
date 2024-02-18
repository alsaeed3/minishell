/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:27:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/18 23:13:45 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

char *expand_dollar_2(char *variable, t_dlr *dlr, t_parse *data)
{
    if (variable[0] == '?')
        return (dlr->i++, ft_itoa(data->exit_status));
	else if (variable[0] == '0')
        return (dlr->i++, ft_strdup("minishell"));
	else if (variable[0] == '#')
		return (dlr->i++, ft_strdup("0"));
	else if (variable[0] == '$')
		return (dlr->i++, ft_itoa(getpid()));
	else if ((variable[0] >= '1' && variable[0] <= '9') \
	|| ft_isalpha(variable[0]) || variable[0] == '*' \
	|| variable[0] == '@' || variable[0] == '!' \
	|| variable[0] == '-')
        return (dlr->i++, ft_strdup(""));
    return (NULL);
}

char *expand_dollar_sign(char *str, t_parse *data)
{
    t_dlr	dlr;

	dlr = (t_dlr){0};
	dlr.ret = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!dlr.ret)
		return (NULL);
	dlr.i = -1;
    while (++dlr.i < (int)ft_strlen(str))
	{
        if (str[dlr.i] == '\'')
		{
            dlr.in_single_quotes = !dlr.in_single_quotes;
            dlr.ret[dlr.j++] = str[dlr.i];
        }
		else if (str[dlr.i] == '\"')
		{
            dlr.in_double_quotes = !dlr.in_double_quotes;
            dlr.ret[dlr.j++] = str[dlr.i];
        }
		else if (str[dlr.i] == '$')
		{
            if (dlr.in_single_quotes)
                dlr.ret[dlr.j++] = str[dlr.i];
			else
			{
                dlr.expanded = expand_dollar_2(str + dlr.i + 1, &dlr, data);
				if (dlr.expanded)
				{
					ft_strcpy(dlr.ret + dlr.j, dlr.expanded);
					dlr.j += ft_strlen(dlr.expanded);
					free_set_null((void **)&dlr.expanded);
				}
				else
					dlr.ret[dlr.j++] = str[dlr.i];;
            }
        }
		else
            dlr.ret[dlr.j++] = str[dlr.i];
    }
	free (str);
    dlr.ret[dlr.j] = '\0';
    return (dlr.ret);
}

t_bool	parse_shell(char *cmd_line, char *str, t_parse **data)
{
	str = ft_strdup(cmd_line);
	if (!str || !str[0])
		return (TRUE);
	str = conv_tabs2spcs(str);
	// ft_putstr_fd("conv_tabs2spcs: ", 2); ft_putchar_fd('{', 2); ft_putstr_fd(str, 2); ft_putendl_fd("}", 2);
	if (check_errors(str))
	{
		(*data)->exit_status = 258;
		return (TRUE);
	}
	str = delete_excess_spcs(str);
	// ft_putstr_fd("delete_excess_spcs: ", 2); ft_putchar_fd('{', 2); ft_putstr_fd(str, 2); ft_putendl_fd("}", 2);
	(*data)->envs_lst = get_envs_lst((*data)->env);
	str = expand_dollar_string(str, (*data)->envs_lst);
	str = expand_dollar_sign(str, *data);
	(*data)->parts_num = find_parts_num(str);
	(*data)->in_rdr_num = find_rdr_num(str, '<', (*data));
	(*data)->inputs_redirections = hold_rdr_names(str, '<', (*data));
	(*data)->inputs_tokens = tokenize_redir(str, (*data), '<');
	// ft_putstr_fd("inputs_redirections[0][0]: ", 2); ft_putchar_fd('{', 2); ft_putstr_fd((*data)->inputs_redirections[0][0], 2); ft_putendl_fd("}", 2);
	// ft_putstr_fd("inputs_redirections[0][1]: ", 2); ft_putchar_fd('{', 2); ft_putstr_fd((*data)->inputs_redirections[0][1], 2); ft_putendl_fd("}", 2);
	find_heredocs_num((*data));
	handle_heredoc((*data));
	(*data)->out_rdr_num = find_rdr_num(str, '>', (*data));
	(*data)->outputs_redirections = hold_rdr_names(str, '>', (*data));
	(*data)->outputs_tokens = tokenize_redir(str, (*data), '>');
	// ft_putstr_fd("outputs_redirections[0][0]: ", 2); ft_putchar_fd('{', 2); ft_putstr_fd((*data)->outputs_redirections[0][0], 2); ft_putendl_fd("}", 2);
	// ft_putstr_fd("outputs_redirections[0][1]: ", 2); ft_putchar_fd('{', 2); ft_putstr_fd((*data)->outputs_redirections[0][1], 2); ft_putendl_fd("}", 2);
	str = conv_redir2spcs(str);
	// ft_putstr_fd("conv_redir2spcs: ", 2); ft_putchar_fd('{', 2); ft_putstr_fd(str, 2); ft_putendl_fd("}", 2);
	str = delete_excess_spcs(str);
	// ft_putstr_fd("delete_excess_spcs: ", 2); ft_putchar_fd('{', 2); ft_putstr_fd(str, 2); ft_putendl_fd("}", 2);
	(*data)->cmds = split_cmds(str);
	// ft_putstr_fd("(*data)->cmds[0][0]: ", 2); ft_putchar_fd('{', 2); ft_putstr_fd((*data)->cmds[0][0], 2); ft_putendl_fd("}", 2);
	// ft_putstr_fd("(*data)->cmds[0][0]: ", 2); ft_putchar_fd('{', 2); ft_putstr_fd((*data)->cmds[0][1], 2);	ft_putendl_fd("}", 2);
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
