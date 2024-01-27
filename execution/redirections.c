/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:38 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:43 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static void ft_error(char *str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

int	redirect_from(t_parse *data, int x)
{
	int 	i;
	int		fd;
	char	*filename;
	
	i = 0;
	filename = NULL;
	while (i < data->in_redir_num[x])
	{
		if(data->inputs_tokens[x][i] == 0)
		{
			filename = data->inputs_redirections[x][i];
			if(open(filename, O_RDONLY) < 0)
			{
				ft_error(strerror(ENOENT));
				data->redir = 0;
				return 1;
			}
		}
		else if (data->inputs_tokens[x][i] == 1)
			filename = data->heredoc_tmp_files[x];
		if (filename)
			fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("Error: Wrong file name or wrong permissions\n", 2);
			data->redir = 0;
			return 1;
		}
		i++;
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
	while (i < data->out_redir_num[x])
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
				data->redir = 0;
				return ;
			}
			i++;
		}
	dup2(fd, 1);
	if (data->fd_out != 1)
		close(data->fd_out);
	data->fd_out = fd;
}
