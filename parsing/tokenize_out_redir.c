/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_out_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:39:54 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/25 22:05:14 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	**tokenize_outputs(char *cmd_line, int parts_num, int *redir_num)
{
	int	**out_tokens;
	int	i;
	int	j;
	int	k;
	int	len;

	out_tokens = ft_calloc(parts_num, sizeof(int *));
	i = -1;
	while (++i < parts_num)
		out_tokens[i] = ft_calloc(redir_num[i], sizeof(int));
	len = ft_strlen(cmd_line);
	i = -1;
	j = 0;
	k = 0;
	while (++i < len)
	{
		if (k >= redir_num[j])
		{
			j++;
			k = 0;
		}
		if (cmd_line[i] == '>' && cmd_line[i + 1] != '>' && cmd_line[i - 1] != '>')
			out_tokens[j][k++] = 0;
		else if (cmd_line[i] == '>' && cmd_line[i + 1] == '>')
		
			out_tokens[j][k++] = 1;
	}
	return (out_tokens);
}

int main(void)
{
	while (1)
	{
		char *input = readline("$> ");
		int	parts_num = find_parts_num(input);
		int *redir_num = find_outfiles_appends_num(input, parts_num);
		int **out_tokens = tokenize_outputs(input, parts_num, redir_num);
		free (input);
		int i = -1;
		int	j;
		while (++i < parts_num)
		{
			j = -1;
			while (++j < redir_num[i])
				printf("part: %d, token: %d = %d\n", i, j, out_tokens[i][j]);
		}
		free (redir_num);
		i = -1;
		while (++i < parts_num)
			free (out_tokens[i]);
		free (out_tokens);
	}
}