/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:16:57 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/09 14:46:56 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	find_heredocs_num(t_parse *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->inputs_redirections && data->inputs_redirections[++i])
	{
		j = -1;
		while (data->inputs_redirections[i][++j])
		{
			if (data->inputs_redirections[i][j + 1] == NULL \
			&& data->inputs_tokens[i][j] == 1)
				data->heredocs_num++;
		}
	}
}

char	*generate_file_names(int pos)
{
	char	*name;
	char	*name2;
	char	*ret_name;
	char	*pos_char;
	char	*tmp;

	name = "/tmp/heredoc";
	pos_char = ft_itoa(pos);
	name2 = ".tmp";
	tmp = ft_strjoin(name, pos_char);
	free_set_null(pos_char);
	ret_name = ft_strjoin(tmp, name2);
	free_set_null(tmp);
	return (ret_name);
}

static t_bool	fake_heredoc(t_hvr *hvr, t_parse *data)
{
	if (data->inputs_redirections[hvr->i][hvr->j + 1] != NULL)
	{
		while (1)
		{
			g_signal = 2;
			hvr->line = readline("> ");
			if (hvr->line == NULL || ft_strcmp(hvr->line, \
			data->inputs_redirections[hvr->i][hvr->j]) == 0)
			{
				free_set_null(hvr->line);
				break ;
			}
		}
		return (TRUE);
	}
	return (FALSE);
}

static void	real_heredoc(t_hvr *hvr, t_parse *data)
{
	if (data->inputs_redirections[hvr->i][hvr->j + 1] == NULL)
	{
		data->heredoc_tmp_files[hvr->k] = generate_file_names(hvr->k + 1);
		hvr->wrfd = open(data->heredoc_tmp_files[hvr->k], \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (hvr->wrfd == -1)
		{
			close (hvr->wrfd);
			unlink(data->heredoc_tmp_files[hvr->k]);
			hvr->wrfd = open(data->heredoc_tmp_files[hvr->k], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		while (1)
		{
			g_signal = 2;
			hvr->line = readline("> ");
			if (process_line(hvr, data))
				break ;
			write(hvr->wrfd, hvr->line, ft_strlen(hvr->line));
			write(hvr->wrfd, "\n", 1);
			free_set_null(hvr->line);
		}
		close(hvr->wrfd);
	}
}

void	handle_heredoc(t_parse *data)
{
	t_hvr	hvr;

	hvr = (t_hvr){0};
	init_hvr(&hvr, data);
	while (data->inputs_redirections && data->inputs_redirections[++hvr.i])
	{
		hvr.j = -1;
		while (data->inputs_redirections[hvr.i][++hvr.j])
		{
			if (data->inputs_tokens[hvr.i][hvr.j] == 1 \
			&& !fake_heredoc(&hvr, data))
				real_heredoc(&hvr, data);
			if (data->inputs_tokens[hvr.i][hvr.j] == 1 && hvr.line)
				free_set_null(hvr.line);
		}
	}
	if (data->heredocs_num)
		data->heredoc_tmp_files[hvr.k] = NULL;
}
