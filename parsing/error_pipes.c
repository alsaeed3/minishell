/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
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
			return (TRUE);
	}
	return (FALSE);
}
