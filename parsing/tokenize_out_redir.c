/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_out_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:39:54 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/26 21:31:40 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	**tokenize_outputs(char *str, t_parse *data)
{
	int	**out_tokens;
	int *redir_num;
	int parts_num;
	int	i;
	int	j;
	t_bool 	quo_trigger;
	char	quo_char;
	int	k;
	int	len;

	if (!data->tot_outredir)
		return (NULL);
	if (data->tot_outredir)
		redir_num = data->out_rdr_num;
	parts_num = data->parts_num;
	redir_num = data->out_rdr_num;
	out_tokens = ft_calloc(parts_num, sizeof(int *));
	i = -1;
	while (++i < parts_num)
		out_tokens[i] = ft_calloc(redir_num[i], sizeof(int));
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
		}
		if ((str[i] == quo_char) && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (str[i] == '|' && !quo_trigger)
		{
			j++;
			k = 0;
		}
		if (i < len - 1 && str[i] == '>' && str[i + 1] != '>' && (i == 0 || str[i - 1] != '>') && !quo_trigger)
			out_tokens[j][k++] = 0;
		else if (i < len - 1 && str[i] == '>' && str[i + 1] == '>' && !quo_trigger)
			out_tokens[j][k++] = 1;
	}
	return (out_tokens);
}

// int main(void)
// {
// 	while (1)
// 	{
// 		char *input = readline("$> ");
// 		int	parts_num = find_parts_num(input);
// 		int *redir_num = find_outfiles_appends_num(input, parts_num);
// 		int **out_tokens = tokenize_outputs(input, parts_num, redir_num);
// 		free (input);
// 		int i = -1;
// 		int	j;
// 		while (++i < parts_num)
// 		{
// 			j = -1;
// 			while (++j < redir_num[i])
// 				printf("part: %d, token: %d = %d\n", i, j, out_tokens[i][j]);
// 		}
// 		free (redir_num);
// 		i = -1;
// 		while (++i < parts_num)
// 			free (out_tokens[i]);
// 		free (out_tokens);
// 	}
// }