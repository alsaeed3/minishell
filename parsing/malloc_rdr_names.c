/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_rdr_names.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 00:45:27 by alsaeed           #+#    #+#             */
/*   Updated: 2024/09/29 10:26:11 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

//  char ***inputs needs to be changes to the structure, 
// then use the structre counterpart.
char	***malloc_rdr_names(int parts_num, int *rdr_num, int **rdr_chars)
{
	char	***rdr_names;
	int		i;
	int		j;

	rdr_names = ft_calloc((parts_num + 1), sizeof(char **));
	if (!rdr_names)
		return (NULL);
	i = -1;
	while (++i < parts_num)
	{
		rdr_names[i] = ft_calloc((rdr_num[i] + 1), sizeof(char *));
		if (!rdr_names[i])
			return (NULL);
		j = -1;
		while (++j < rdr_num[i])
		{
			rdr_names[i][j] = ft_calloc((rdr_chars[i][j] + 1), sizeof(char));
			if (!rdr_names[i][j])
				return (NULL);
		}
	}
	return (rdr_names);
}

void	free_char_triple_pointer(char ****pointer)
{
	int		i;
	int		j;
	int		len;

	if (!pointer || !(*pointer))
		return ;
	i = -1;
	while ((*pointer)[++i])
	{
		j = -1;
		len = ft_array_size((*pointer)[i]);
		while (++j <= len)
		{
			if ((*pointer)[i][j])
				free_set_null((void **)&(*pointer)[i][j]);
		}
		if ((*pointer)[i])
			free_set_null((void **)&(*pointer)[i]);
	}
	free_set_null((void **)pointer);
}
