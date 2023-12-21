/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_inputs_chars_num.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:29:14 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/21 21:40:39 by alsaeed          ###   ########.fr       */
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
	i = 0;
	if ((cmd_line[0] == '<' || cmd_line[0] == ' '))
		i = 1;
	if ((cmd_line[0] == '<' && cmd_line[1] == ' '))
		i = 2;
	while (i < len)
	{
		if (cmd_line[i] == '|' || cmd_line[i] == '>' || cmd_line[i] != ' ' || cmd_line[i] != '<')
		{
			*reach = i;
			return ;
		}
		else
			(*char_num)++;
		i++;
	}
}

int	**find_icm_num(char *cmd_line, int pipes_num, int *inputs_num)
{
	int	i;
	int j;
	int	k;
	int	len;
	bool	trigger;
	int	char_num;
	int **icm;

	icm = ft_calloc(pipes_num, sizeof(int *));
	len = ft_strlen(cmd_line);
	i = -1;
	while (++i < pipes_num)
		icm[i] = ft_calloc(inputs_num[i], sizeof(int));
	trigger = false;
	i = -1;
	k = 0;
	j = 0;
	while (++i < len)
	{
		if (cmd_line[i] == '|')
		{
			k = 0;
			j++;
		}
		// else if (cmd_line[i] == '>' || cmd_line[i] == '\'' || cmd_line[i] == '"')
		// 	jump_over_out(cmd_line + i ,&i);
		else if ((cmd_line[i] == '<' && cmd_line[i + 1] != '<' && cmd_line[i - 1] != '<') && !trigger)
		{
			char_num = 0;
			trigger = true;
			if (cmd_line[i + 1] == ' ')
				i++;
		}
		else if ((cmd_line[i] == '<' && cmd_line[i + 1] == '<') && !trigger)
		{
			char_num = 0;
			trigger = true;
			i++;
			if (cmd_line[i + 1] == ' ')
				i++;
		}
		else if ((cmd_line[i] != '<' || cmd_line[i] != ' ' || cmd_line[i] != '|') && trigger)
			char_num++;
		if ((cmd_line[i + 1] == '<' || cmd_line[i + 1] == ' ' || cmd_line[i + 1] == '|' || cmd_line[i + 1] == '\0') && trigger)
		{
			icm[j][k++] = char_num;
			trigger = false;
		}
	}
	return (icm);
}

int main()
{
		char *cmd_line = readline("$> ");
		int pipes_num = find_pipes_num(cmd_line);
		int *inh = find_infiles_heredocs_num(cmd_line, pipes_num);
		int **icm = find_icm_num(cmd_line, pipes_num, inh);
		free(cmd_line);
		int i = -1;
		int j;
		while (++i < pipes_num)
		{
			j = -1;
			while (++j < inh[i])
			{
				printf("part: %d, redir: %d, chars: %d\n", i, j, icm[i][j]);
			}
		}
		for (int i = 0; i < pipes_num; i++)
		{
			free(icm[i]);
		}
		free(icm);
		free(inh);
    return 0;
}
