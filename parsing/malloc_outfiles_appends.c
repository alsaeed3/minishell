/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_outfiles_appends.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 00:45:27 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/10 21:02:01 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

//  char ***inputs needs to be changes to the structure, then use the structre counterpart.
char	***malloc_file_names(int parts_num, int *each_part_redir_num, int **file_name_chars_num)
{
	char	***file_names;
	int		i;
	int		j;

	i = -1;
	file_names = ft_calloc((parts_num + 1), sizeof(char **));
	if (!file_names)
		return (NULL);
	while (++i < parts_num)
	{
		file_names[i] = ft_calloc((each_part_redir_num[i] + 1), sizeof(char *));
		if (!file_names[i])
			return (NULL);
		j = -1;
		while (++j < each_part_redir_num[i])
		{
			file_names[i][j] = ft_calloc((file_name_chars_num[i][j] + 1), sizeof(char));
			if (!file_names[i][j])
				return (NULL);
		}
	}
	return (file_names);
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
