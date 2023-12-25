/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_inputs_chars_num.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:	if (ret[j] == ' ')
		ret[j] = '\0';
	else
		ret[++j] = '\0';+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:29:14 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/24 22:21:00 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// to find each infile/heredoc file name characters and store them into
// a double pointer to use it later in mallocing

void	find_ichar_num(char *cmd_line, int *char_num, int *reach)
{
	int		i;
	int		len;

	len = ft_strlen(cmd_line);
	i = 0;
	if ((cmd_line[0] == '<' || cmd_line[0] == ' '))
		i = 1;
	if ((cmd_line[0] == '<' && cmd_line[1] == ' '))
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

int	**find_ic_num(char *cmd_line, int pipes_num, int *inputs_num)
{
	int	i;
	int j;
	int	k;
	int	len;
	bool	redi_trigger;
	bool	quo_trigger;
	char	quo_char;
	int	char_num;
	int **icm;

	icm = ft_calloc(pipes_num + 1, sizeof(int *));
	len = ft_strlen(cmd_line);
	i = -1;
	while (++i < pipes_num + 1)
		icm[i] = ft_calloc(inputs_num[i], sizeof(int));
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
			quo_char = cmd_line[i];
			quo_trigger = true;
		}
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger && !redi_trigger)
			jump_over_quote(cmd_line, &i, len);
		else if((cmd_line[i] == quo_char) && redi_trigger && quo_char)
			quo_trigger = false;
		else if (((cmd_line[i] == '"' || cmd_line[i] == '\'' || cmd_line[i] == '<' || cmd_line[i] == '>' || cmd_line[i] == '|')) && redi_trigger && quo_trigger)
			char_num++;
		if ((cmd_line[i] == '<' && cmd_line[i + 1] != '<' && cmd_line[i - 1] != '<') && !redi_trigger && !quo_trigger)
		{
			char_num = 0;
			redi_trigger = true;
			if (cmd_line[i + 1] == ' ')
				i++;
		}
		if ((cmd_line[i] == '<' && cmd_line[i + 1] == '<') && !redi_trigger && !quo_trigger)
		{
			char_num = 0;
			redi_trigger = true;
			i++;
			if (cmd_line[i + 1] == ' ')
				i++;
		}
		if (((cmd_line[i] != '<' && cmd_line[i] != '>' && cmd_line[i] != ' ' && cmd_line[i] != '|' && cmd_line[i] != '\'' && cmd_line[i] != '"') && redi_trigger))
			char_num++;
		if ((cmd_line[i + 1] == '<' || cmd_line[i + 1] == '>' || cmd_line[i + 1] == ' ' || cmd_line[i + 1] == '|' || cmd_line[i + 1] == '\0') && redi_trigger && !quo_trigger)
		{
			icm[j][k++] = char_num;
			redi_trigger = false;
		}
	}
	return (icm);
}

int main()
{
	while (1)
	{
		char *cmd_line = readline("$> ");
		int pipes_num = find_pipes_num(cmd_line);
		int *inh = find_infiles_heredocs_num(cmd_line, pipes_num);
		int **icm = find_ic_num(cmd_line, pipes_num, inh);
		free(cmd_line);
		int j;
		int i = -1;
		while (++i < pipes_num + 1)
		{
			j = -1;
			while (++j < inh[i])
				printf("part: %d, redir: %d, chars: %d\n", i, j, icm[i][j]);
		}
		i = -1;
		while (++i < pipes_num + 1)
			free(icm[i]);
		free(icm);
		free(inh);
	}
    return 0;
}
