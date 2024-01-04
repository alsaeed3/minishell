/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_outfiles_appends.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 00:45:27 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/05 00:46:34 by alsaeed          ###   ########.fr       */
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

void	free_outputs(char ***outputs ,int parts_num, int *each_part_outputs_num)
{
	int		i;
	int		j;

	if (outputs)
	{
		i = -1;
		while (++i < (parts_num))
		{
			if (outputs[i])
			{
				j = -1;
				while (++j < each_part_outputs_num[i])
				{
					if (outputs[i][j])
					{
						free (outputs[i][j]);
						outputs[i][j] = NULL;
					}
				}
				free (outputs[i]);
				outputs[i] = NULL;
			}
		}
		free (outputs);
		outputs = NULL;
	}
}
