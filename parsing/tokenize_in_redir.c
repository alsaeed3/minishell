/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:01:18 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/25 18:39:05 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	**tokenize_inputs(char *cmd_line, int pipes_num, int *redir_num)
{
	int	**in_tokens;
	int	i;
	int	j;
	int	k;
	int	len;

	in_tokens = ft_calloc(pipes_num + 1, sizeof(int *));
	i = -1;
	while (++i < pipes_num + 1)
		in_tokens[i] = ft_calloc(redir_num[i], sizeof(int));
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
		if (cmd_line[i] == '<' && cmd_line[i + 1] != '<' && cmd_line[i - 1] != '<')
			in_tokens[j][k++] = 0;
		else if (cmd_line[i] == '<' && cmd_line[i + 1] == '<')
		
			in_tokens[j][k++] = 1;
	}
	return (in_tokens);
}

int main(void)
{
	while (1)
	{
		char *input = readline("$> ");
		int	pipes_num = find_pipes_num(input);
		int *redir_num = find_infiles_heredocs_num(input, pipes_num);
		int **in_tokens = tokenize_inputs(input, pipes_num, redir_num);
		free (input);
		int i = -1;
		int	j;
		while (++i < pipes_num + 1)
		{
			j = -1;
			while (++j < redir_num[i])
				printf("part: %d, token: %d = %d\n", i, j, in_tokens[i][j]);
		}
		free (redir_num);
		i = -1;
		while (++i < pipes_num + 1)
			free (in_tokens[i]);
		free (in_tokens);
	}
}