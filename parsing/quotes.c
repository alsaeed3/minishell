/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:08:50 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/04 21:02:21 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

bool	check_quotes(char *str)
{
	int		i;
	int		len;
	char	trigger;
	bool	flag;
	bool	in_quote;
	
	i = -1;
	flag = false;
	in_quote = false;
	len = ft_strlen(str);
	while (++i < len)
	{
		if ((str[i] == '\'' || str[i] == '"') && !in_quote)
		{
			in_quote = true;	
			flag = true;
			trigger = str[i];
			while (++i < len)
			{
				if (str[i] == trigger)
				{
					in_quote = false;
					flag = false;
					break;
				}
			}
		}
	}
	return (flag);
}

void	remove_str_quotes(char *str, char **ret, int char_num)
{
	int	i;
	int	j;
	int	k;
	int trigger;
	int	len;

	i = -1;
	k = -1;
	len = (int)ft_strlen(str);
	*ret = malloc(sizeof(char) * (char_num + 1));
	while (++i < len)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			trigger = (int)str[i];
			j = i;
			while (++j < len)
			{
				if (str[j] == trigger)
					break;
				(*ret)[++k] = str[j];
			}
			i = j;
		}
		if (str[i] != ' ' && str[i] != '\'' && str[i] != '"')
			(*ret)[++k] = str[i];
	}
	(*ret)[++k] = '\0';
}

// int main(void)
// {
// 	int	char_num = 0;
// 	char *ret;

// 	while(1)
// 	{
// 		char *input = readline("$ ");
// 		if (check_quotes(input))
// 			printf("Error\n");
// 		else
// 		{
// 			printf ("correct\n");
// 			// get_str_quotes(input, &ret, char_num);
// 			// printf("%s\n", ret);
// 			// free (ret);
// 		}
// 		printf("-----\n");
// 		free (input);
// 	}
//     return 0;
// }
		