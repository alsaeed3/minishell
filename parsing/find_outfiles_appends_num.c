/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_outfiles_appends_num.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:11:01 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/20 14:47:35 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	find_outfiles_appends_num(char *str, int *outfiles_num, int *appends_num)
{
	int	i;
	int	outfiles_appends_num;

	i = -1;
	outfiles_appends_num = 0;
	while (++i < ft_strlen(str))
	{
		if (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>')
		{
			(*outfiles_num)++;
			outfiles_appends_num++;
		}
		else if (str[i] == '>' && str[i + 1] == '>' && str[i - 1] != '>' && str[i + 2] != '>')
		{
			(*appends_num)++;
			outfiles_appends_num++;
		}
	}
	return (outfiles_appends_num);
}

// int main(void)
// {
// 	while (1)
// 	{
// 		int outfiles_num = 0;
// 		int appends_num = 0;
// 		int outfiles_appends_num = 0;
// 		char *input = readline("$> ");
// 		outfiles_appends_num = find_outfiles_appends_num(input, &outfiles_num, &appends_num);
// 		printf("outfiles_num = %d\n", outfiles_num);
// 		printf("appends_num = %d\n", appends_num);
// 		printf("outfiles_appends_num = %d\n", outfiles_appends_num);
// 		free(input);
// 	}
// }