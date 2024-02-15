/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:38 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/15 19:09:05 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

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
		if (data->heredocs_num && filename && access(filename, F_OK) != 0)
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

	filename = get_file_name(data, x);
	if (!filename)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_error(strerror(errno));
		return (2);
	}
	if (dup2(fd, 0) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	redirect_to(t_parse *data, int x)
{
	char	*filename;
	int		fd;
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
		{
			perror("Error");
			return (127);
		}
		i++;
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	redirect_from_pipe(t_parse *data, t_pipe *pipes)
{
	char	*filename;
	int		fd;

	filename = NULL;
	filename = get_file_name(data, pipes->i);
	if (!filename)
		free_close_fd(data, 0, 1, pipes);
	close(STDIN_FILENO);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		free_set_null((void **)&pipes->pipe_fds);
		free_set_null((void **)&pipes->pid);
		free_close_fd(data, 0, 2, pipes);
	}
	return (fd);
}

int	redirect_to_pipe(t_parse *data, t_pipe *pipes)
{
	char	*filename;
	int		fd;
	int		i;
	int		flags;

	i = -1;
	while (++i < data->out_rdr_num[pipes->i])
	{
		filename = data->outputs_redirections[pipes->i][i];
		flags = O_RDWR | O_CREAT;
		if (data->outputs_tokens[pipes->i][i] == 1)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		close(STDOUT_FILENO);
		fd = open(filename, flags, S_IRUSR | S_IWUSR);
		if (fd < 0)
		{
			perror("Error");
			free_close_fd(data, 0, 2, pipes);
		}
	}
	return (fd);
}
