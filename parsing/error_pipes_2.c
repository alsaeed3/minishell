/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipes_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:52:54 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/16 21:42:27 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

bool check_end_pipe_redir(char *str)
{
	int 	i;
	int		j;
	bool	trigger;
	
	i = -1;
	trigger = false;
	while (++i < ft_strlen(str))
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			j = i;
			while (++j < ft_strlen(str + i))
			{
				if (str[j] != ' ')
					trigger = true;
				else if ((str[j + 1] == '\0' || str[j + 1] == '|' || str[j + 1] == '<' || str[j + 1] == '>')  && !trigger)
					return (true);
			}
		}
	}
	return (false);
}

// error: double pipe or more (next to each other), if (< < or > > or >>> or <<<) or more
bool	check_pipe_red_2(char *str)
{
	int	i;
	
	i = -1;
	while (++i < ft_strlen(str))
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == '|' || str[i + 1] == '\0' || check_end_pipe_redir(str + i))
				return (true);
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == '<' || str[i + 1] == '>' || str[i + 1] == ' ')
			{
				if (str[i + 2] == '<' || str[i + 2] == '>')
					return (true);
			}
		}
	}
	return (false);
}

int main(void)
{
	char *str;
	while (1)
	{
		str = readline("> ");
		if (check_duo_pipe(str))
			printf("error\n");
		else
			printf("correct\n");
		free(str);
	}
	return (0);
}