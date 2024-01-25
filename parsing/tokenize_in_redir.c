/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_in_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:01:18 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/25 21:20:26 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// static t_bool check_redir_num(int *redir_num, int parts_num)
// {
// 	int	i;
// 	t_bool check;

// 	i = -1;
// 	check = FALSE;
// 	while (++i < parts_num)
// 	{
// 		if (redir_num[i])
// 			return (true);
// 	}
// 	return (check);
// }

int	**tokenize_inputs(char *str)
{
	printf("tokenize_inputs\n");
	int	**in_tokens;
	int *redir_num;
	int parts_num;
	int	i;
	int	j;
	t_bool 	quo_trigger;
	char	quo_char;
	int	k;
	int	len;

	parts_num = find_parts_num(str);
	redir_num = find_rdr_num(str, '<');
	// if (!check_redir_num(redir_num, parts_num))
	// 	return (NULL);
	in_tokens = ft_calloc(parts_num, sizeof(int *));
	i = -1;
	while (++i < parts_num)
		in_tokens[i] = ft_calloc(redir_num[i], sizeof(int));
	len = ft_strlen(str);
	quo_trigger = FALSE;
	quo_char = '\0';
	i = -1;
	j = 0;
	k = 0;
	while (++i < len)
	{
		if ((str[i] == '"' || str[i] == '\'') && !quo_trigger)
		{
			quo_char = str[i++];
			quo_trigger = TRUE;
			if (str[i] == quo_char)
			{
				quo_char = '\0';
				quo_trigger = FALSE;
			}
		}
		else if ((str[i] == quo_char) && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (str[i] == '|' && !quo_trigger)
		{
			j++;
			k = 0;
		}
		if (i < len - 1 && str[i] == '<' && str[i + 1] != '<' && (i == 0 || str[i - 1] != '<') && !quo_trigger)
			in_tokens[j][k++] = 0;
		else if (i < len - 1 && str[i] == '<' && str[i + 1] == '<' && !quo_trigger)
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