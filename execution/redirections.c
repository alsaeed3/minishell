/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:38 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/11 15:51:22 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static char	*get_file_name(t_parse *data, int x)
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
		if(access(filename, F_OK) != 0)
		{
			ft_error(strerror(ENOENT));
			return (NULL);
		}
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
	if (!filename)
		return (1);
	else
		fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_error(strerror(ENOENT));
		return (2);
	}
	if(!data->cmds[x][0])
		return (1);
	if (dup2(fd, 0) == -1)
		ft_putendl_fd("dup2 failed", 2);
	close(fd);
	if (data->fd_in != 0)
		close(data->fd_in);
	data->fd_in = fd;
	return (0);
}

int	redirect_to(t_parse *data, int x)
{
	int		fd;
	char	*filename;
	int		i;

	i = 0;
	while (i < data->out_rdr_num[x])
	{
		filename = data->outputs_redirections[x][i];
		if (data->outputs_tokens[x][i] == 1)
			fd = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		else
			fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (fd < 0)
			return (ft_putendl_fd("Error: wrong permissions", 2), 127);
		i++;
	}
	if(!data->cmds[x][0])
		return (1);
	if (dup2(fd, 1) == -1)
		ft_putendl_fd("dup2 failed", 2);
	close(fd);
	if (data->fd_out != 1)
		close(data->fd_out);
	data->fd_out = fd;
	return (0);
}
