/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_excess_spcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:24:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/14 20:40:25 by alsaeed          ###   ########.fr       */
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
	int		len;
	t_bool	quo_trigger;
	char	quo_char;
	int		size;

	len = ft_strlen(cmd_line);
	i = -1;
	size = 0;
	if (cmd_line[0] == ' ')
			jump_over_spaces(cmd_line, &i);
	quo_trigger = FALSE;
	while (++i < len)
	{
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_trigger = TRUE;
			quo_char = cmd_line[i];
		}
		else if (cmd_line[i] == quo_char && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (cmd_line[i] == ' ' && cmd_line[i + 1] == ' ' && !quo_trigger)
		{
			size++;
			while (cmd_line[i] == ' ')
				i++;
			if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
			{
				quo_trigger = TRUE;
				quo_char = cmd_line[i];
			}
		}
		size++;
	}
	return (size);
}

char	*delete_excess_spcs(char *cmd_line)
{
	int		i;
	int		j;
	int		len;
	t_bool	quo_trigger;
	char	quo_char;
	int		size;
	char	*ret;

	len = ft_strlen(cmd_line);
	size = size_without_spcs(cmd_line);
	ret = ft_calloc(size + 1, sizeof(char));
	j = 0;
	i = -1;
	quo_trigger = FALSE;
	if (cmd_line[0] == ' ')
			jump_over_spaces(cmd_line, &i);
	while (++i < len)
	{
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_trigger = TRUE;
			quo_char = cmd_line[i];
		}
		else if (cmd_line[i] == quo_char && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (cmd_line[i] == ' ' && cmd_line[i + 1] == ' ' && !quo_trigger)
		{
			if (i < len - 1 || (i == len - 1 && cmd_line[len - 1] != ' '))
				ret[j++] = cmd_line[i];
			while (cmd_line[i] == ' ')
				i++;
			if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
			{
				quo_trigger = TRUE;
				quo_char = cmd_line[i];
			}
		}
		if (i < len - 1 || (i == len - 1 && cmd_line[len - 1] != ' '))
				ret[j++] = cmd_line[i];
	}
	if (ret[j])
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