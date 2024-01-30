/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:16:57 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/30 23:57:56 by alsaeed          ###   ########.fr       */
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
	free (pos_char);
	ret_name = ft_strjoin(tmp, name2);
	free (tmp);
	return (ret_name);
}

static t_bool	fake_heredoc(t_hvr *hvr, t_parse *data)
{
	if (data->inputs_redirections[hvr->i][hvr->j + 1] != NULL \
	&& data->inputs_tokens[hvr->i][hvr->j] == 1)
	{
		while (1)
		{
			hvr->line = readline("> ");
			if (hvr->line == NULL || hvr->line[0] == '\0' \
			|| ft_strcmp(hvr->line, \
			data->inputs_redirections[hvr->i][hvr->j]) == 0)
			{
				free(hvr->line);
				break ;
			}
		}
		return (TRUE);
	}
	return (FALSE);
}

static void	real_heredoc(t_hvr *hvr, t_parse *data)
{
	if (data->inputs_redirections[hvr->i][hvr->j + 1] == NULL \
	&& data->inputs_tokens[hvr->i][hvr->j] == 1)
	{
		data->heredoc_tmp_files[hvr->k] = generate_file_names(hvr->k + 1);
		hvr->wrfd = open(data->heredoc_tmp_files[hvr->k], \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (hvr->wrfd == -1)
		{
			perror("Error opening temporary file");
			free (data->heredoc_tmp_files);
			return ;
		}
		while (1)
		{
			hvr->line = readline("> ");
			if (process_line(hvr, data))
				break ;
			write(hvr->wrfd, hvr->line, ft_strlen(hvr->line));
			write(hvr->wrfd, "\n", 1);
		}
	}
}

void	handle_heredoc(t_parse *data)
{
	t_hvr	hvr;

	init_hvr(&hvr, data);
	while (data->inputs_redirections && data->inputs_redirections[++hvr.i])
	{
		hvr.j = -1;
		while (data->inputs_redirections[hvr.i][++hvr.j])
		{
			if (!fake_heredoc(&hvr, data))
				real_heredoc(&hvr, data);
			if (hvr.line)
				free(hvr.line);
			close(hvr.wrfd);
		}
	}
	if (data->heredocs_num)
		data->heredoc_tmp_files[hvr.k] = NULL;
	if (!data->heredocs_num)
	{
		free(data->heredoc_tmp_files);
		data->heredoc_tmp_files = NULL;
	}
}
