/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:46:44 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/20 11:09:50 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void ft_free(char **cmd)
{
	int i;
	i = 0;
	while(cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}
