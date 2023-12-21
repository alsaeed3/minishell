/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/20 20:38:26 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int main(void)
{
	int	i = -1;
	char *cmd_line = readline("$> ");
	char *ret;
	
	if (check_quotes(cmd_line))
	{
		printf("Error\nquotes\n");
		return (1);
	}
	ret = conv_tabs2spcs(cmd_line);
	ret = delete_excess_spcs(ret);
	if (check_pipe_redir(ret))
	{
		printf("Error\ncheck_pipe_redir\n");
		return (1);
	}
	else if (check_pipe_red_2(ret))
	{
		printf("Error\ncheck_pipe_red_2(\n");
		return (1);
	}
	
}
