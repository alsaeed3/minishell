/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_outfiles_appends.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 00:45:27 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/06 04:50:58 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

//  char ***inputs needs to be changes to the structure, then use the structre counterpart.
char	***malloc_outputs(int parts_num, int *each_part_outputs_num, int **file_name_chars_num)
{
	char	***outputs;
	int		i;
	int		j;

	i = -1;
	outputs = ft_calloc((parts_num + 2), sizeof(char **));
	if (!outputs)
		return (NULL);
	while (++i < (parts_num))
	{
		outputs[i] = ft_calloc((each_part_outputs_num[i] + 1), sizeof(char *));
		if (!outputs[i])
			return (NULL);
		j = -1;
		while (++j < each_part_outputs_num[i])
		{
			outputs[i][j] = ft_calloc((file_name_chars_num[i][j] + 1), sizeof(char));
			if (!outputs[i][j])
				return (NULL);
		}
	}
	return (outputs);
}

void	free_char_triple_pointer(char ***pointer)
{
	int		i;
	int		j;

	if (pointer)
	{
		i = -1;
		while (pointer[++i])
		{
			j = -1;
			while (pointer[i][++j])
			{
				if (pointer[i][j])
				{
					free (pointer[i][j]);
					pointer[i][j] = NULL;
				}
			}
			if (pointer[i])
			{
				free (pointer[i]);
				pointer[i] = NULL;
			}
		}
		free (pointer);
		pointer = NULL;
	}
}
