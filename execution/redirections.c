/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:38 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/18 23:12:46 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

t_bool	check_dir_out(char *str)
{
	struct stat	path_stat;
	int			i;
	int 		len;
	int			size;
	char		*direc;
	t_bool 		dir;

	i = -1;
	dir = FALSE;
	direc = NULL;
	len = ft_strlen(str);
	if (str[0] == '.' && str[1] == '/')
	{
		i += 2;
		while (++i < len)
		{
			if (str[i] == '/')
			{
				dir = TRUE;
				size = i;
			}
		}
	}
	if (dir)
	{
		direc = ft_substr(str, 0, size);
		if (stat(direc, &path_stat) != 0)
		{
			free_set_null((void **)&direc);
			return (TRUE);
		}
		if (S_ISDIR(path_stat.st_mode) != 1)
		{
			free_set_null((void **)&direc);
			return (TRUE);
		}
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
		if (filename && access(filename, F_OK) != 0 || check_dir_out(filename))
		{
			print_message(filename, ": No such file or directory");
			return (NULL);
		}
		if (filename && (access(filename, F_OK) == 0 && access(filename, W_OK) == -1) || filename[0] == '/')
		{
			print_message(filename, ": Permission denied");
			return (NULL);
		}
	}
	return (filename);
}

int	redirect_from(t_parse *data)
{
	int		fd;
	char	*filename;

	filename = get_file_name(data, 0);
	if (!filename)
		return (1);
	if (access(filename, F_OK) == 0 && access(filename, R_OK) == -1)
	{
		ft_error(strerror(errno));
		return (2);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_error(strerror(errno));
		return (2);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redirect_to(t_parse *data)
{
	char		*filename;
	int			fd;
	int			i;
	int			flags;

	i = -1;
	while (++i < data->out_rdr_num[0])
	{
		filename = data->outputs_redirections[0][i];
		if (check_dir_out(filename))
		{
            print_message(filename, ": No such file or directory");
			return (1);
		}
		if ((access(filename, F_OK) == 0 && access(filename, R_OK) == -1) || filename[0] == '/')
		{
            print_message(filename, ": Permission denied");
			return (1);
		}
		flags = O_RDWR | O_CREAT;
		if (data->outputs_tokens[0][i] == 1)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(filename, flags, S_IRUSR | S_IWUSR);
		if (fd < 0)
		{
			perror("Error");
			data->exit_status = 1;
			return (1);
		}
	}
	dup2(fd, STDOUT_FILENO);
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
			data->exit_status = 1;
			free_close_fd(data, 0, 1, pipes);
		}
	}
	return (fd);
}
