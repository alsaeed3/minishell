/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:08:50 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/20 14:47:57 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

bool	check_quotes(char *str, int *char_num)
{
	int	i;
	int j;
	int trigger;
	bool flag;
	
	i = -1;
	j = 0;
	trigger = 0;
	flag = false;

	while (++i < ft_strlen(str))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			flag = true;
			trigger = (int)str[i];
			j = i;
			while (++j < (ft_strlen(str)))
			{
				if (str[j] == trigger)
				{
					flag = false;
					break;
				}
				(*char_num)++;
			}
			i = j;
		}
		if (str[i] != ' ' && str[i] != '\'' && str[i] != '"')
			(*char_num)++;
	}
	return (flag);
}

void	remove_str_quotes(char *str, char **ret, int char_num)
{
	int	i;
	int	j;
	int	k;
	int trigger;

	i = -1;
	k = -1;
	*ret = malloc(sizeof(char) * (char_num + 1));
	while (++i < ft_strlen(str))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			trigger = (int)str[i];
			j = i;
			while (++j < ft_strlen(str))
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
// 		char *input = readline("Enter something: ");
// 		if (check_quotes(input, &char_num))
// 			printf("Error\n");
// 		else
// 		{
// 			get_str_quotes(input, &ret, char_num);
// 			printf("%s\n", ret);
// 			free (ret);
// 		}
// 		printf("-----\n");
// 		free (input);
// 	}
//     return 0;
// }
		