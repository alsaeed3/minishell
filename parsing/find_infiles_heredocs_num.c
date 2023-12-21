/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles_heredocs_num.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:47:49 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/20 21:23:54 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	*find_infiles_heredocs_num(char *str, int pipes_num)
{
	int		i;
	int		j;
	int		len;
	char	trigger;
	int		*infiles_heredocs_num;

	i = -1;
	j = 0;
	len = ft_strlen(str);
	infiles_heredocs_num = ft_calloc(pipes_num + 1 ,sizeof(int));
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
		if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
			infiles_heredocs_num[j]++;
		else if (str[i] == '<' && str[i + 1] == '<' && str[i - 1] != '<' && str[i + 2] != '<')
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
// 		int pipes_num = find_pipes_num(input);
// 		infiles_heredocs_num = find_infiles_heredocs_num(input, pipes_num);
// 		free (input);
// 		int i = -1;
// 		while (++i < (pipes_num + 1))
// 			printf("part %d: %d\n", i, infiles_heredocs_num[i]);
// 		free (infiles_heredocs_num);
// 	}
// }