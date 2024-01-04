/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_excess_spcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:24:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/04 16:27:24 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static void	jump_over_spaces(char *cmd_line, int *i)
{
	(*i)++;
	while (cmd_line[*i] == ' ')
		(*i)++;
	(*i)--;
}

static int size_without_spcs(char *cmd_line)
{
	int		i;
	int		j;
	int		len;
	char	trigger;
	int		size;

	len = ft_strlen(cmd_line);
	j = -1;
	i = -1;
	size = 0;
	if (cmd_line[0] == ' ')
			jump_over_spaces(cmd_line, &i);
	while (++i < len)
	{
		if (cmd_line[i] == '\"' || cmd_line[i] == '\'')
		{
			size++;
			trigger = cmd_line[i++];
			while (cmd_line[i] != trigger)
			{
				size++;
				i++;
			}
			size++;
		}
		else if (cmd_line[i] == ' ' && cmd_line[i + 1] == ' ')
		{
			size++;
			while (cmd_line[i] == ' ')
				i++;
			i--;
		}
		else
			size++;
	}
	if (cmd_line[len - 1] == ' ')
		size--;
	return (size);
}

char	*delete_excess_spcs(char *cmd_line)
{
	int		i;
	int		j;
	int		len;
	char	trigger;
	char	*ret;

	len = ft_strlen(cmd_line);
	ret = ft_calloc(size_without_spcs(cmd_line) + 1, sizeof(char));
	j = -1;
	i = -1;
	if (cmd_line[0] == ' ')
			jump_over_spaces(cmd_line, &i);
	while (++i < len)
	{
		if (cmd_line[i] == '\"' || cmd_line[i] == '\'')
		{
			ret[++j] = cmd_line[i];
			trigger = cmd_line[i++];
			while (cmd_line[i] != trigger)
				ret[++j] = cmd_line[i++];
			ret[++j] = trigger;
		}
		else if (cmd_line[i] == ' ' && cmd_line[i + 1] == ' ')
		{
			ret[++j] = cmd_line[i];
			while (cmd_line[i] == ' ')
				i++;
			i--;
		}
		else
			ret[++j] = cmd_line[i];
	}
	if (ret[j] == ' ')
		ret[j] = '\0';
	else
		ret[++j] = '\0';
	return (ret);
}

/* To test delete_excess_spcs function */
// int main(void)
// {
// 	int	i;
// 	char *str;
// 	while(1)
// 	{
// 		char *input = readline("$> ");
// 		// char *input = "  <  '1     23'  |  << '  12 ' ";
// 		str = delete_excess_spcs(input);
// 		free(input);
// 		printf("%s\n",str);
// 		free(str);
// 	}
// }

/* To test size_without_spcs function */
// int main(void)
// {
// 	int	i;
// 	int size;
// 	size = 0;
// 	while(1)
// 	{
// 		char *input = readline("$> ");
// 		size = size_without_spcs(input);
// 		free(input);
// 		printf("%d\n",size);
// 	}
// }