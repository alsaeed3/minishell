/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:51:39 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/05 16:52:41 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/main.h"

void	ft_trim_input(char **input)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while ((*input)[i] == ' ')
		i++;
	while ((*input)[i])
	{
		(*input)[j] = (*input)[i];
		i++;
		j++;
	}
	(*input)[j] = '\0';
	i = ft_strlen(*input) - 1;
	while ((*input)[i] == ' ')
		i--;
	(*input)[i + 1] = '\0';
}
