/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles_heredocs_num.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:47:49 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/20 14:47:27 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	*find_infiles_heredocs_num(char *str, int pipes_num)
{
	int	i;
	int j;
	int k;
	int	*infiles_heredocs_num;

	i = -1;
	j = 0;
	infiles_heredocs_num = ft_calloc(pipes_num + 1 ,sizeof(int));
	while (++i < ft_strlen(str))
	{
		if (str[i] == '|')
			j++;
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
// 		int i = -1;
// 		char *input = readline("$> ");
// 		infiles_heredocs_num = find_infiles_heredocs_num(input, find_pipes_num(input));
// 		free (input);
// 		while (i < find_pipes_num(input) + 1)
// 			printf("part 1: %d\n", infiles_heredocs_num[i++]);
// 		free (infiles_heredocs_num);
// 	}
// }