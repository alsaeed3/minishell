/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:38 by habu-zua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/13 19:10:44 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/19 21:37:40 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

<<<<<<< HEAD
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

int redirect_from(t_parse *data, int x)
=======
int	redirect_from(t_parse *data)
>>>>>>> main
{
    int fd;
    char *filename;

<<<<<<< HEAD
    filename = get_file_name(data, x);
    if (!filename)
        return 1;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        ft_error(strerror(errno));
        return 2;
    }
    if (dup2(fd, 0) == -1)
    {
        ft_putendl_fd("dup2 failed", 2);
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}

int redirect_to(t_parse *data, int x)
{
    char *filename;
    int fd;
    int i;

    i = 0;
    while (i < data->out_rdr_num[x])
    {
        filename = data->outputs_redirections[x][i];
        if (data->outputs_tokens[x][i] == 1)
            fd = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
        else
            fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd < 0) {
            ft_putendl_fd("Error: wrong permissions", 2);
            return 127;
        }
        i++;
    }
    if (dup2(fd, 1) == -1)
    {
        ft_putendl_fd("dup2 failed", 2);
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}
=======
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

t_bool	is_dir_out(char *filename)
{
	if (check_dir_out(filename))
	{
		print_message(filename, ": No such file or directory");
		return (TRUE);
	}
	if ((access(filename, F_OK) == 0 && access(filename, W_OK) == -1) \
	|| filename[0] == '/')
	{
		print_message(filename, ": Permission denied");
		return (TRUE);
	}
	return (FALSE);
}

int	redirect_to(t_parse *data)
{
	t_rdr		rdr;

	rdr = (t_rdr){0};
	rdr.i = -1;
	while (++rdr.i < data->out_rdr_num[0])
	{
		rdr.filename = data->outputs_redirections[0][rdr.i];
		if (is_dir_out(rdr.filename))
			return (1);
		rdr.flags = O_RDWR | O_CREAT;
		if (data->outputs_tokens[0][rdr.i] == 1)
			rdr.flags |= O_APPEND;
		else
			rdr.flags |= O_TRUNC;
		rdr.fd = open(rdr.filename, rdr.flags, S_IRUSR | S_IWUSR);
		if (rdr.fd < 0)
		{
			perror("Error");
			data->exit_status = 1;
			return (1);
		}
	}
	dup2(rdr.fd, STDOUT_FILENO);
	close(rdr.fd);
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
>>>>>>> main
