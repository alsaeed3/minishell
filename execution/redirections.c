/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:38 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/31 01:24:42 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static char *get_file_name(t_parse *data, int x)
{
	int i;
	char *filename;
	
	filename = NULL;
	i = 0;
	while(i < data->in_rdr_num[x])
	{
		if(data->inputs_tokens[x][i] == 0 && data->inputs_redirections[x][i])
			filename = data->inputs_redirections[x][i];
		else if(data->inputs_tokens[x][i] == 1 && data->heredocs_num)
			filename = data->heredoc_tmp_files[x];
		i++;
	}
	return (filename);
}

int	redirect_from(t_parse *data, int x)
{
	int		fd;
	char	*filename;
	
	fd = 0;
	filename = NULL;
	
	filename = get_file_name(data, x);
	if(!filename)
		return 1;
	else
		fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_error(strerror(ENOENT));
		return 1;
	}
	dup2(fd, 0);
	if (data->fd_in != 0)
		close(data->fd_in);
	data->fd_in = fd;
	return 0;
}


void redirect_to(t_parse *data, int x)
{
	int		fd;
	char	*filename;
	int i;
	i = 0;
	while (i < data->out_rdr_num[x])
		{
			filename = data->outputs_redirections[x][i];
			if (data->outputs_tokens[x][i] == 1)
				fd = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
			else
				fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			free(filename);
			if (fd < 0)
			{
				ft_putstr_fd("Error: wrong permissions\n", 2);
				// data->redir = 0;
				return ;
			}
			i++;
		}
	dup2(fd, 1);
	if (data->fd_out != 1)
		close(data->fd_out);
	data->fd_out = fd;
}
