/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_inputs_chars_num.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:29:14 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/19 20:29:08 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// to find each infile/heredoc file name characters and store them into
// a double pointer to use it later in mallocing
int		**find_inputs_chars_num(char *cmd_line)
{
	int	i;
	int	j;
	int	k;
	int	len;
	int **icm;

	i = -1;
	j = -1;
	k = -1;
	len = ft_strlen(cmd_line);
	while(++i < len)
	{
		k = -1;
		if (cmd_line[i] == '|')
			j++;
		if (cmd_line[i] == '<' || (cmd_line[i] == '<' && cmd_line[i + 1] == '<'))
			
	}	
}