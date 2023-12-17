/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles_heredocs_num.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:47:49 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/17 13:17:27 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	find_infiles_heredocs_num(char *str, int *infiles_num, int *heredocs_num)
{
	int	i;
	int	infiles_heredocs_num;

	i = -1;
	infiles_heredocs_num = 0;
	while (++i < ft_strlen(str))
	{
		if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
		{
			(*infiles_num)++;
			infiles_heredocs_num++;
		}
		else if (str[i] == '<' && str[i + 1] == '<' && str[i - 1] != '<' && str[i + 2] != '<')
		{
			(*heredocs_num)++;
			infiles_heredocs_num++;
		}
	}
	return (infiles_heredocs_num);
}

int main(void)
{
	while (1)
	{
		int infiles_num = 0;
		int heredocs_num = 0;
		int infiles_heredocs_num = 0;
		char *input = readline("$> ");
		infiles_heredocs_num = find_infiles_heredocs_num(input, &infiles_num, &heredocs_num);
		printf("infiles_num = %d\n", infiles_num);
		printf("heredocs_num = %d\n", heredocs_num);
		printf("infiles_heredocs_num = %d\n", infiles_heredocs_num);
		free(input);
	}
}