/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_infile_heredocs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:41:29 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/19 19:24:00 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

//  char ***inputs needs to be changes to the structure, then use the structre counterpart.
bool	malloc_inputs(char ***inputs ,int pipes_num, int *each_part_inputs_num, int **file_name_chars_num)
{
	int		i;
	int		j;

	i = -1;
	inputs = ft_calloc((pipes_num + 2), sizeof(char **));
	while (++i < (pipes_num + 1))
	{
		inputs[i] = ft_calloc((each_part_inputs_num[i] + 1), sizeof(char *));
		j = -1;
		while (++j < each_part_inputs_num[i])
			inputs[i][j] = ft_calloc((file_name_chars_num[i][j] + 1), sizeof(char));
	}
	return (false);
}

void	free_inputs(char ***inputs ,int pipes_num, int *each_part_inputs_num, int **file_name_chars_num)
{
	int		i;
	int		j;

	if (inputs)
	{
		i = -1;
		while (++i < (pipes_num + 1))
		{
			if (inputs[i])
			{
				j = -1;
				while (++j < each_part_inputs_num[i])
				{
					if (inputs[i][j])
					{
						free (inputs[i][j]);
						inputs[i][j] = NULL;
					}
				}
				free (inputs[i]);
				inputs[i] = NULL;
			}
		}
		free (inputs);
		inputs = NULL;
	}
}
