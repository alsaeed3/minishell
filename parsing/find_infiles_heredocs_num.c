/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles_heredocs_num.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:47:49 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/06 05:12:20 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	*find_infiles_heredocs_num(char *str, int parts_num)
{
	int		i;
	int		j;
	int		len;
	char	trigger;
	int		*infiles_heredocs_num;

	i = -1;
	j = 0;
	len = ft_strlen(str);
	infiles_heredocs_num = ft_calloc(parts_num ,sizeof(int));
	while (++i < len)
	{
		if (str[i] == '|')
			j++;
		if (str[i] == '\'' || str[i] == '"')
		{
			trigger = str[i];
			while (++i < len)
			{
				if (str[i] == trigger)
					break;
			}
		}
		if ((i <= len - 1) && str[i] == '<' && str[i + 1] != '<' && (i == 0 || str[i - 1] != '<'))
			infiles_heredocs_num[j]++;
		else if ((i <= len - 2) && str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<')
			infiles_heredocs_num[j]++;
	}
	return (infiles_heredocs_num);
}

// int main(void)
// {
// 	while (1)
// 	{
// 		int *infiles_heredocs_num;
// 		char *input = readline("$> ");
// 		int parts_num = find_parts_num(input);
// 		infiles_heredocs_num = find_infiles_heredocs_num(input, parts_num);
// 		free (input);
// 		int i = -1;
// 		while (++i < (parts_num))
// 			printf("part %d: %d\n", i, infiles_heredocs_num[i]);
// 		free (infiles_heredocs_num);
// 	}
// }