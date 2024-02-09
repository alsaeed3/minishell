/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_delegate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:34:20 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/09 22:11:33 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	exec_delegator(t_parse *parser)
{
	int	ret;

	ret = 0;
	if (parser->parts_num == 1)
	{
		parser->h_index = 0;
		ret = handle_single(parser->cmds[0], parser, 0);
	}
	else
	{
		parser->h_index = -1;
		ret = handle_pipe(parser);
	}
	g_signal = 1;
	while (parser->heredocs_num)
	{
		unlink(parser->heredoc_tmp_files[parser->heredocs_num - 1]);
		parser->heredocs_num--;
	}
	parser->exit_status = ret;
}

char *ft_strreplace(char *orig, char *rep, char *with) 
{
	char *result; // the return string
	char *ins;    // the next insert point
	char *tmp;    // varies
	int len_rep;  // length of rep (the string to remove)
	int len_with; // length of with (the string to replace rep with)
	int len_front; // distance between rep and end of last rep
	int count;    // number of replacements

	if (!orig || !rep)
		return NULL;
	len_rep = ft_strlen(rep);
	if (len_rep == 0)
		return NULL;
	if (!with)
		with = "";
	len_with = ft_strlen(with);
	ins = orig;
	for (count = 0; (tmp = strstr(ins, rep)); ++count) {
		ins = tmp + len_rep;
	}
	result = malloc(ft_strlen(orig) + (len_with - len_rep) * count + 1);
	tmp = result;

	if (!result)
		return NULL;
	while (count--) {
		ins = strstr(orig, rep);
		len_front = ins - orig;
		tmp = strncpy(tmp, orig, len_front) + len_front;
		tmp = strcpy(tmp, with) + len_with;
		orig += len_front + len_rep; 
	}
	strcpy(tmp, orig);
	return result;
}

void expand_dolar_sign(char **inputs, t_parse *data)
{
	int	i;
	int	j;
	char	*tmp;

	i = 0;
	while (inputs[i])
	{
		j = 0;
		while (inputs[i][j])
		{
			if (inputs[i][j] == '$' )
			{
				if(inputs[i][j + 1] == '?')
				{
					tmp = ft_itoa(data->exit_status);
					inputs[i] = ft_strreplace(inputs[i], "$?", tmp);
				}
				else if(inputs[i][j + 1] == '0')
				{
					tmp = ft_strdup("minishell");
					inputs[i] = ft_strreplace(inputs[i], "$0", tmp);
				}
				else if (ft_isdigit(inputs[i][j + 1]) || inputs[i][j + 1] == '*' || ft_isalpha(inputs[i][j + 1]))
					break;
				free(tmp);
			}
			
			j++;
		}
		i++;
	}
	
}

int	handle_single_pipe(char **inputs, t_parse *data, int x)
{
	int	oldfd[2];
	int	ret;

	expand_dolar_sign(inputs, data);
	ret = 0;
	oldfd[0] = dup(0);
	oldfd[1] = dup(1);
	if (data->in_rdr_num[x] > 0)
		if (redirect_from(data, x))
			return (1);
	if (data->out_rdr_num[x] > 0)
		if (redirect_to(data, x))
			return (127);
	ret = choose_action(inputs, data, x);
	dup2(oldfd[0], 0);
	dup2(oldfd[1], 1);
	close(oldfd[0]);
	close(oldfd[1]);
	return (ret);
}

int	choose_action(char **cmd, t_parse *data, int x)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd[0], "echo") == 0)
		handle_echo(data, x);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		handle_pwd(data);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		handle_cd(cmd, data);
	else if (ft_strcmp(cmd[0], "env") == 0)
		handle_env(data->env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		handle_exit(cmd, data);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ret = handle_export(cmd, data);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		handle_unset(cmd, data);
	else
		ret = handle_exec(cmd, data);
	return (ret);
}
