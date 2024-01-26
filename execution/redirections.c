/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:38 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/26 15:02:42 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void redirect_from(t_parse *data, int x)
{
	int 	i;
	int		fd;
	char	*filename;
	
	i = 0;
	filename = NULL;
	while (i < data->in_redir_num[x])
	{
		if(data->inputs_tokens[x][i] == 0 && data->inputs_redirections[x][i + 1] == NULL)
		{
			printf("heerreeee\n");
			filename = data->inputs_redirections[x][i];
		}
		else if (data->inputs_tokens[x][i] == 1 && data->inputs_redirections[x][i + 1] == NULL)
		{
			printf("heerreeee else\n");
			filename = data->heredoc_tmp_files[x];
		}
		if (filename)
		{
			printf("filename = {%s}\n", filename);
			fd = open(filename, O_RDONLY);
			printf("fd: %d\n", fd);
		}
		if (fd < 0)
		{
			ft_putstr_fd("Error: Wrong file name or wrong permissions\n", 2);
			data->redir = 0;
			return ;
		}
		i++;
	}
	dup2(fd, 0);
	if (data->fd_in != 0)
		close(data->fd_in);
	data->fd_in = fd;
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
