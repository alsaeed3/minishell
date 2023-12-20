/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipes_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:52:54 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/20 12:34:06 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

bool check_end_pipe(char *str)
{
	int		i;
	bool	trigger;
	int		len;
	
	len = ft_strlen(str);
	trigger = false;
	i = -1;
	while (++i < len)
	{
		if (str[i] != ' ' && str[i] != '\t')
			trigger = true;
		else if ((str[i + 1] == '\0' || str[i + 1] == '|') && !trigger)
			return (true);
	}
	return (false);
}

bool check_redir_end(char *str)
{
	int	i;
	bool	trigger;
	int		len;
	
	len = ft_strlen(str);
	trigger = false;
	i = -1;
	if (str[i] == '<' || str[i] == '>')
		i = 0;
	while (++i < len)
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '<' && str[i] != '>' && str[i] != '|')
			trigger = true;
		else if ((str[i] == '\0' || str[i] == '<'\
			|| str[i] == '>' || str[i] == '|') && !trigger)
			return (true);
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
		if ((str[i] == '<' && str[i + 1] == '>') || (str[i] == '>' && str[i + 1] == '<'))
			return (true);
		else if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<') \
				|| str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			return (true);
		else if ((str[i] == '<' || str[i] == '>'))
		{
			if (str[i + 1] == '|' || str[i + 1] == '\0' || check_redir_end(str + (i + 1)))
				return (true);
		}
		else if (str[i] == '|')
		{
			if (str[i + 1] == '|' || str[i + 1] == '\0' || check_end_pipe(str + (i + 1)))
				return (true);
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
		if (check_pipe_red_2(str))
			printf("error\n");
		else
			printf("correct\n");
		free(str);
	}
	return (0);
}