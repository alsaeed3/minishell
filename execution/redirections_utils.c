/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:59:51 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/19 21:37:30 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	init_rdr(char *str, t_rdr *rdr)
{
	*rdr = (t_rdr){0};
	rdr->i = -1;
	rdr->dir = FALSE;
	rdr->direc = NULL;
	rdr->len = ft_strlen(str);
}

t_bool	get_direc(t_rdr *rdr, char *str)
{
	rdr->direc = ft_substr(str, 0, rdr->size);
	if (stat(rdr->direc, &rdr->path_stat) != 0)
	{
		free_set_null((void **)&rdr->direc);
		return (TRUE);
	}
	if (S_ISDIR(rdr->path_stat.st_mode) != 1)
	{
		free_set_null((void **)&rdr->direc);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	check_dir_out(char *str)
{
	t_rdr	rdr;

	init_rdr(str, &rdr);
	if (str[0] == '.' && str[1] == '/')
	{
		rdr.i += 2;
		while (++rdr.i < rdr.len)
		{
			if (str[rdr.i] == '/')
			{
				rdr.dir = TRUE;
				rdr.size = rdr.i;
			}
		}
	}
	if (rdr.dir)
		if (get_direc(&rdr, str))
			return (TRUE);
	return (FALSE);
}

t_bool	is_filename(char *filename)
{
	if (filename && (access(filename, F_OK) != 0 \
		|| check_dir_out(filename)))
	{
		print_message(filename, ": No such file or directory");
		return (TRUE);
	}
	if (filename && ((access(filename, F_OK) == 0 \
	&& access(filename, W_OK) == -1)))
	{
		print_message(filename, ": Permission denied");
		return (TRUE);
	}
	return (FALSE);
}

char	*get_file_name(t_parse *data, int x)
{
	int		i;
	char	*filename;

	filename = NULL;
	i = -1;
	while (++i < data->in_rdr_num[x])
	{
		if (data->inputs_tokens[x][i] == 0 && data->inputs_redirections[x][i])
			filename = data->inputs_redirections[x][i];
		else if (data->inputs_tokens[x][i] == 1 && data->heredocs_num \
		&& data->h_index < data->heredocs_num)
			filename = data->heredoc_tmp_files[data->h_index];
		if (is_filename(filename))
			return (NULL);
	}
	return (filename);
}
