/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:01:18 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/25 16:05:02 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	*tokenize_inputs(char *cmd_line)
{
	int	*tokens;
	int	i;
	int	len;

	tokens = ft_calloc();
	len = ft_strlen(cmd_line);
	i = -1;
	while (++i < len)
	{
		
	}
}

int main(void)
{
	char *input = readline("$> ");
	
}