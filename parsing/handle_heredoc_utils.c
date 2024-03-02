/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:24:19 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/21 16:31:17 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

t_bool	process_line(t_hvr *hvr, t_parse *data)
{
	char	c[2];

	if (hvr->line == NULL || ft_strcmp(hvr->line, \
	data->inputs_redirections[hvr->i][hvr->j]) == 0 \
	|| (null_deli(data, hvr) && hvr->line[0] == '\0') || g_signal == 1)
	{
		hvr->rdfd = open(data->heredoc_tmp_files[hvr->k], O_RDONLY);
		if (hvr->rdfd < 0)
			return (TRUE);
		if (!access(data->heredoc_tmp_files[hvr->k++], F_OK) \
		&& ((read(hvr->rdfd, c, 1)) <= 0))
		{
			data->heredocs_num--;
			unlink(data->heredoc_tmp_files[hvr->k - 1]);
			free_set_null((void **)&data->heredoc_tmp_files[hvr->k - 1]);
			hvr->k--;
		}
		close(hvr->rdfd);
		return (TRUE);
	}
	return (FALSE);
}

void	init_hvr(t_hvr *hvr, t_parse *data)
{
	hvr->i = -1;
	hvr->k = 0;
	hvr->line = NULL;
	hvr->wrfd = 0;
	data->heredoc_tmp_files = NULL;
	if (data->heredocs_num > 0)
	{
		data->heredoc_tmp_files = ft_calloc(data->heredocs_num + 1, \
		sizeof(char *));
		if (!data->heredoc_tmp_files)
			return ;
	}
}
