/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_inputs_chars_num.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 00:57:18 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/11 21:08:12 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/parser.h"

// to find each infile/heredoc file name characters and store them into
// a double pointer to use it later in mallocing

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

int	**find_ic_num(char *cmd_line)
{
	int	i;
	int j;
	int	k;
	int	len;
	int parts_num;
	int *inputs_num;
	t_bool	redi_trigger;
	t_bool	quo_trigger;
	char	quo_char;
	int	char_num;
	int **icm;

	parts_num = find_parts_num(cmd_line);
	inputs_num = find_infiles_heredocs_num(cmd_line);
	icm = ft_calloc(parts_num, sizeof(int *));
	len = ft_strlen(cmd_line);
	i = -1;
	while (++i < parts_num)
		icm[i] = ft_calloc(inputs_num[i], sizeof(int));
	redi_trigger = FALSE;
	quo_trigger = FALSE;
	i = -1;
	k = 0;
	j = 0;
	while (++i < len )
	{
		if((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger && redi_trigger)
		{
			quo_char = cmd_line[i++];
			quo_trigger = TRUE;
		}
		else if((cmd_line[i] == quo_char) && redi_trigger && quo_char)
		{
			i++;
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (cmd_line[i] == '|' && !quo_trigger && !redi_trigger)
		{
			j++;
			k = 0;
		}
		if (i < len - 1 && (cmd_line[i] == '<' && cmd_line[i + 1] != '<' && (i == 0 || cmd_line[i - 1] != '<')) && !redi_trigger && !quo_trigger)
		{
			char_num = 0;
			redi_trigger = TRUE;
			i++;
			if (cmd_line[i] == ' ')
				i++;
		}
		else if (i < len - 1 && (cmd_line[i] == '<' && cmd_line[i + 1] == '<') && !redi_trigger && !quo_trigger)
		{
			char_num = 0;
			redi_trigger = TRUE;
			i += 2;
			if (cmd_line[i] == ' ')
				i++;
		}
		if ((cmd_line[i] == ' ' || cmd_line[i] == '<' || cmd_line[i] == '>') && redi_trigger && !quo_trigger)
		{
			redi_trigger = FALSE;
			k++;
			char_num = 0;
		}
		else if ((cmd_line[i] == '<' || cmd_line[i] == '>' || cmd_line[i] == ' ' || cmd_line[i] == '|' || cmd_line[i] != quo_char) && quo_trigger && redi_trigger)
			icm[j][k] = ++char_num;
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && redi_trigger && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
			continue ;
		}
		if (cmd_line[i] != '>' && cmd_line[i] != '<' && cmd_line[i] != '|' && !quo_trigger && redi_trigger)
			icm[j][k] = ++char_num;
	}
	return (icm);
}

// int main()
// {
// 	while (1)
// 	{
// 		char *cmd_line = readline("$> ");
// 		int parts_num = find_parts_num(cmd_line);
// 		int *inh = find_infiles_heredocs_num(cmd_line, parts_num);
// 		int **icm = find_ic_num(cmd_line, parts_num, inh);
// 		free(cmd_line);
// 		int j;
// 		int i = -1;
// 		while (++i < parts_num)
// 		{
// 			j = -1;
// 			while (++j < inh[i])
// 				printf("part: %d, redir: %d, chars: %d\n", i, j, icm[i][j]);
// 		}
// 		i = -1;
// 		while (++i < parts_num)
// 			free(icm[i]);
// 		free(icm);
// 		free(inh);
// 	}
//     return 0;
// }
