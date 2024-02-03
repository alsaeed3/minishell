/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:24:19 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/03 14:04:13 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_bool	process_line(t_hvr *hvr, t_parse *data)
{
	if (hvr->line == NULL || hvr->line[0] == '\0' \
	|| ft_strcmp(hvr->line, \
	data->inputs_redirections[hvr->i][hvr->j]) == 0)
	{
		hvr->rdfd = open(data->heredoc_tmp_files[hvr->k], O_RDONLY);
		if (!access(data->heredoc_tmp_files[hvr->k++], F_OK) \
		&& ((read(hvr->rdfd, hvr->line, 1)) <= 0))
		{
			data->heredocs_num--;
			unlink(data->heredoc_tmp_files[hvr->k - 1]);
			free (data->heredoc_tmp_files[hvr->k - 1]);
			data->heredoc_tmp_files[hvr->k - 1] = NULL;
			hvr->k--;
		}
		close(hvr->rdfd);
		free(hvr->line);
		hvr->line = NULL;
		return (TRUE);
	}
	return (FALSE);
}

void	init_hvr(t_hvr *hvr, t_parse *data)
{
	hvr->i = -1;
	hvr->k = 0;
	// hvr->line = NULL;
	hvr->wrfd = 0;
	// data->heredoc_tmp_files = NULL;
	// if (data->heredocs_num > 0)
	// {
	data->heredoc_tmp_files = ft_calloc(data->heredocs_num + 1, \
	sizeof(char *));
	if (!data->heredoc_tmp_files)
		return ;
	// }
}
