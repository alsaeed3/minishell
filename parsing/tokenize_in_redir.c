/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_in_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:01:18 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/07 13:48:17 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	**tokenize_inputs(char *cmd_line, int parts_num, int *redir_num)
{
	int	**in_tokens;
	int	i;
	int	j;
	t_bool 	quo_trigger;
	char	quo_char;
	int	k;
	int	len;

	in_tokens = ft_calloc(parts_num, sizeof(int *));
	i = -1;
	while (++i < parts_num)
		in_tokens[i] = ft_calloc(redir_num[i], sizeof(int));
	len = ft_strlen(cmd_line);
	quo_trigger = FALSE;
	quo_char = '\0';
	i = -1;
	j = 0;
	k = 0;
	while (++i < len)
	{
		if ((cmd_line[i] == '"' || cmd_line[i] == '\'') && !quo_trigger)
		{
			quo_char = cmd_line[i++];
			quo_trigger = TRUE;
		}
		else if ((cmd_line[i] == quo_char) && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (cmd_line[i] == '|' && !quo_trigger)
		{
			j++;
			k = 0;
		}
		if (i < len - 1 && cmd_line[i] == '<' && cmd_line[i + 1] != '<' && (i == 0 || cmd_line[i - 1] != '<'))
			in_tokens[j][k++] = 0;
		else if (i < len - 2 && cmd_line[i] == '<' && cmd_line[i + 1] == '<' && cmd_line[i + 2] != '<' && (i == 0 || cmd_line[i - 1] != '<'))
			in_tokens[j][k++] = 1;
	}
	return (in_tokens);
}

// int main(void)
// {
// 	while (1)
// 	{
// 		char *read = readline("$> ");
// 		char *input = ft_strdup(read);
// 		int	parts_num = find_parts_num(input);
// 		int *redir_num = find_infiles_heredocs_num(input, parts_num);
// 		int **in_tokens = tokenize_inputs(input, parts_num, redir_num);
// 		free (input);
// 		int	j;
// 		int i = -1;
// 		while (++i < parts_num)
// 		{
// 			j = -1;
// 			while (++j < redir_num[i])
// 				printf("part: %d, token: %d = %d\n", i, j, in_tokens[i][j]);
// 		}
// 		free (redir_num);
// 		i = -1;
// 		while (++i < parts_num)
// 			free (in_tokens[i]);
// 		free (in_tokens);
// 	}
// }