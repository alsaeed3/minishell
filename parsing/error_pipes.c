/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:10:41 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/04 23:57:28 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// errors: pipe at the beginning, pipe at the end, redirection symbol at the end
bool	check_pipe_redir(char *line)
{
	int	i;
	int len;

	len = ft_strlen(line);
	i = -1;
	while (++i < len)
	{
		if (line[0] == '|' || line[len - 1] == '|')
			return (true);
		else if ((line[i] == '<' || line[i] == '>') && line[i + 1] == '\0')
			return (true);
	}
	return (false);
}

// int main(void)
// {
// 	int		i;
// 	bool	check;

// 	while (1)
// 	{
// 		char *input = readline("Enter line: ");
// 		check = check_pipe_redir(input);
// 		if (!check)
// 			printf("Correct\n");
// 		else if (check == true)
// 			printf("Error\n");
// 		printf("-----\n");
// 		free(input);
// 	}
// }