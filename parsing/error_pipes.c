/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:10:41 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/06 05:31:30 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// errors: pipe at the beginning, pipe at the end, redirection symbol at the end
t_bool	check_pipe_redir(char *line)
{
	int	i;
	int len;

	len = ft_strlen(line);
	i = -1;
	while (++i < len)
	{
		if (line[0] == '|' || line[len - 1] == '|')
			return (TRUE);
		else if ((line[i] == '<' || line[i] == '>') && line[i + 1] == '\0')
			return (TRUE);
	}
	return (FALSE);
}

// int main(void)
// {
// 	int		i;
// 	t_bool	check;

// 	while (1)
// 	{
// 		char *input = readline("Enter line: ");
// 		check = check_pipe_redir(input);
// 		if (!check)
// 			printf("Correct\n");
// 		else if (check == TRUE)
// 			printf("Error\n");
// 		printf("-----\n");
// 		free(input);
// 	}
// }