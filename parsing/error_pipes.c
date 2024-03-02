/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:10:41 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/07 16:44:21 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// errors: pipe at the beginning, pipe at the end, redirection symbol at the end
t_bool	check_pipe_redir(char *cmd_line)
{
	int	i;
	int len;

	len = ft_strlen(cmd_line);
	i = -1;
	while (++i < len)
	{
		if (cmd_line[0] == '|' || cmd_line[len - 1] == '|')
			return (TRUE);
		else if ((cmd_line[i] == '<' || cmd_line[i] == '>') && cmd_line[i + 1] == '\0')
=======
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:10:41 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/11 11:37:59 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

t_bool	check_pipe_redir(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = -1;
	while (++i < len)
	{
		if (str[0] == '|' || str[len - 1] == '|')
			return (TRUE);
		else if ((str[len - 1] == '<' || str[len - 1] == '>'))
>>>>>>> main
			return (TRUE);
	}
	return (FALSE);
}
<<<<<<< HEAD

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
=======
>>>>>>> main
