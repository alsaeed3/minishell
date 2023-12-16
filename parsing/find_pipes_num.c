/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pipes_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:45:33 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/16 21:45:47 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	find_pipes_num(char *str)
{
	int	i;
	int	pipe_num;

	i = -1;
	pipe_num = 0;
	while (++i < ft_strlen(str))
	{
		if (str[i] == '|')
			pipe_num++;
	}
	return (pipe_num);
}