/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:10:41 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/12 20:42:51 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// errors: pipe at the beginning, pipe at the end, redirection symbol at the end
bool	check_pipe_redir(char *line)
{
	int	i;
	int len;
	char last_two[3];

	len = ft_strlen(line);
	last_two[0] = line[len - 2];
	last_two[1] = line[len - 1];
	last_two[2] = '\0';
	i = -1;
	while (++i < len)
	{
		if (line[0] == '|' || line[len - 1] == '|')
			return (true);
		else if (line[len - 1] == '<' || line[len - 1] == '>')
			return (true);
		else if (!ft_strcmp(last_two, "<<") || !ft_strcmp(last_two, ">>"))
			return (true);
	}
	return (false);
}

int main(void)
{
	int		i;
	bool	check;

	while (1)
	{
		char *input = readline("Enter line: ");
		check = check_pipe_redir(input);
		if (!check)
			printf("Correct\n");
		else if (check == true)
			printf("Error\n");
		printf("-----\n");
		free(input);
	}
}