/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_outputs_chars_num.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 22:12:29 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/25 22:05:14 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	find_ochar_num(char *cmd_line, int *char_num, int *reach)
{
	int		i;
	int		len;

	len = ft_strlen(cmd_line);
	i = 0;
	if ((cmd_line[0] == '>' || cmd_line[0] == ' '))
		i = 1;
	if ((cmd_line[0] == '>' && cmd_line[1] == ' '))
		i = 2;
	while (i < len)
	{
		if (cmd_line[i] == '|' || cmd_line[i] == '>' || cmd_line[i] != ' ' || cmd_line[i] != '<')
		{
			*reach = i;
			return ;
		}
		else
			(*char_num)++;
		i++;
	}
}

void	jump_over_quote(char *cmd_line, int *i, int len)
{
	char	quo_char;

	quo_char = cmd_line[*i];
	(*i)++;
	while (*i < len)
	{
		if (cmd_line[*(i)] == quo_char)
		{
			(*i)++;
			break;
		}
		(*i)++;
	}
}

int	**find_oc_num(char *cmd_line, int parts_num, int *outputs_num)
{
	int	i;
	int j;
	int	k;
	int	len;
	bool	redi_trigger;
	bool	quo_trigger;
	char	quo_char;
	int	char_num;
	int **ocm;

	ocm = ft_calloc(parts_num, sizeof(int *));
	len = ft_strlen(cmd_line);
	i = -1;
	while (++i < parts_num)
		ocm[i] = ft_calloc(outputs_num[i], sizeof(int));
	redi_trigger = false;
	quo_trigger = false;
	i = -1;
	k = 0;
	j = 0;
	while (++i < len)
	{
		if (cmd_line[i] == '|' && !quo_trigger && !redi_trigger)
		{
			k = 0;
			j++;
		}
		if((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger && redi_trigger)
		{
			quo_char = cmd_line[i++];
			quo_trigger = true;
		}
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger && !redi_trigger)
			jump_over_quote(cmd_line, &i, len);
		else if((cmd_line[i] == quo_char) && redi_trigger && quo_char)
			quo_trigger = false;
		else if (((cmd_line[i] == '"' || cmd_line[i] == '\'' || cmd_line[i] == '<' || cmd_line[i] == '>' || cmd_line[i] == '|')) && redi_trigger && quo_trigger)
			char_num++;
		if ((cmd_line[i] == '>' && cmd_line[i + 1] != '>' && cmd_line[i - 1] != '>') && !redi_trigger && !quo_trigger)
		{
			char_num = 0;
			redi_trigger = true;
			if (cmd_line[i + 1] == ' ')
				i++;
		}
		if ((cmd_line[i] == '>' && cmd_line[i + 1] == '>') && !redi_trigger && !quo_trigger)
		{
			char_num = 0;
			redi_trigger = true;
			i++;
			if (cmd_line[i + 1] == ' ')
				i++;
		}
		if (((cmd_line[i] != '<' && cmd_line[i] != '>' && cmd_line[i] != ' ' && cmd_line[i] != '|' && cmd_line[i] != '\'' && cmd_line[i] != '"') && redi_trigger))
			char_num++;
		if (cmd_line[i] == ' ' && redi_trigger && quo_trigger)
			char_num++;
		if ((cmd_line[i + 1] == '<' || cmd_line[i + 1] == '>' || cmd_line[i + 1] == ' ' || cmd_line[i + 1] == '|' || cmd_line[i + 1] == '\0') && redi_trigger && !quo_trigger)
		{
			ocm[j][k++] = char_num;
			redi_trigger = false;
		}
	}
	return (ocm);
}

int main()
{
	while (1)
	{
		char *cmd_line = readline("$> ");
		int parts_num = find_parts_num(cmd_line);
		int *oan = find_outfiles_appends_num(cmd_line, parts_num);
		int **oc = find_oc_num(cmd_line, parts_num, oan);
		free(cmd_line);
		int j;
		int i = -1;
		while (++i < parts_num)
		{
			j = -1;
			while (++j < oan[i])
				printf("part: %d, redir: %d, chars: %d\n", i, j, oc[i][j]);
		}
		i = -1;
		while (++i < parts_num)
			free(oc[i]);
		free(oc);
		free(oan);
	}
    return 0;
}
