/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_inputs_chars_num.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:29:14 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/20 15:41:33 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// to find each infile/heredoc file name characters and store them into
// a double pointer to use it later in mallocing

void	find_char_num(char *cmd_line, int *char_num, int *reach)
{
	int		i;
	int		len;

	len = ft_strlen(cmd_line);
	i = -1;
	if (cmd_line[0] == '>' || cmd_line[0] == '<')
		i = 0;
	if (cmd_line[++i] == ' ')
	{
		while (++i < len)
		{
			if (cmd_line[i] != ' ')
				break;
		}
	}
	else
		i--;
	while (i < len)
	{
		if (cmd_line[i] == ' ' || cmd_line[i] == '<' || cmd_line[i] == '>' || cmd_line[i] == '|')
		{
			*reach = i;
			return ;
		}
		else
			(*char_num)++;
		i++;
	}
}

int	**find_infiles_heredocs_num(char *cmd_line, int pipes_num, int *inputs_num)
{
	int	i;
	int	j;
	int	k;
	int	reach;
	int	char_num;
	int	len;
	int **icm;

	i = -1;
	j = 0;
	char_num = 0;
	reach = 0;
	len = ft_strlen(cmd_line);
	icm = ft_calloc(pipes_num, sizeof(int *));
	while(++i < len)
	{
		icm[j] = ft_calloc(inputs_num[j], sizeof(int));
		k = 0;
		if (cmd_line[i] == '|')
			j++;
		if ((cmd_line[i] == '<' && cmd_line[i + 1] != '<') || (cmd_line[i] == '<' && cmd_line[i + 1] == '<'))
		{
			find_char_num(cmd_line + (i + 1), &char_num, &reach);
			icm[j][k] = char_num;
			k++;
			i = reach;
		}
	}
	return (icm);
}

// int main(void)
// {
// 	int	i = -1;
// 	int j = -2;
	
	
// }