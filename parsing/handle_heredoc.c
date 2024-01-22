/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:16:57 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/22 08:33:36 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	find_heredocs_num(t_parse *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->parts_num)
	{
		j = -1;
		while (++j < data->in_redir_num[i])
		{
			if (data->inputs_tokens[i][j] == 1)
				data->heredocs_num++;
		}
	}
}

void	find_heredocs_ends(t_parse *data)
{
	int	i;
	int	j;
	int k;

	data->heredocs_ends = ft_calloc((data->heredocs_num) + 1, sizeof(char *));
	i = -1;
	k = 0;
	while (data->inputs_redirections[++i])
	{
		j = -1;
		while (data->inputs_redirections[i][++j] && k < (data->heredocs_num))
		{
			if (data->inputs_tokens[i][j] == 1)
				data->heredocs_ends[k++] = ft_strdup(data->inputs_redirections[i][j]);
		}
	}
	data->heredocs_ends[k] = NULL;
}

void	handle_heredoc(t_parse *data)
{
    char	*line;
    int		tmp_fd;
	char	**heredoc_line;
	char	*tmp;
	int		i;
	
	heredoc_line = ft_calloc((data->heredocs_num) + 1, sizeof(char *));
    // Open a temporary file for writing
	i = -1;
    while (++i < data->heredocs_num)
	{
		tmp_fd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp_fd == -1) {
			perror("Error opening temporary file");
			return ;
		}
		// Read lines from the user until the end marker is entered
		while (1) 
		{
			line = readline("> ");
			if (line == NULL || line[0] == '\0' || ft_strcmp(line, data->heredocs_ends[i]) == 0) {
				free(line);
				break;
			}
			// Write the line to the temporary file
			write(tmp_fd, line, ft_strlen(line));
			write(tmp_fd, "\n", 1);
			free(line);
		}
		// Close the temporary file
		close(tmp_fd);
		// Open the temporary file for reading
		tmp_fd = open("temp.txt", O_RDONLY);
		if (tmp_fd == -1) 
		{
			perror("Error opening temporary file");
			return ;
		}
		// Read the heredoc content from the temporary file
		line = get_next_line(tmp_fd);
		while (line) 
		{
			tmp = ft_strjoin(heredoc_line[i], line);
			if (!tmp)
			{
				free(line);
				free(heredoc_line[i]);
				return ;
			}
			free(heredoc_line[i]);
			heredoc_line[i] = tmp;
			free(line);
			line = get_next_line(tmp_fd);
		}
    	close(tmp_fd);
		if (unlink("temp.txt") != 0)
		{
			perror("Error deleting temporary file");
			return ;
		}
	}
	heredoc_line[i] = NULL;
    // Close the temporary file
    // Delete the temporary file
    data->hd_usr_input = heredoc_line;
	replace_heredoc(data);
}

void	replace_heredoc(t_parse *data)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (++i < data->parts_num && data->heredocs_num)
	{
		j = -1;
		while (++j < data->in_redir_num[i] && k < data->heredocs_num)
		{
			if (data->inputs_tokens[i][j] == 1 && data->inputs_redirections[i][j])
			{
				free (data->inputs_redirections[i][j]);
				data->inputs_redirections[i][j] = ft_strdup((data->hd_usr_input[k++]));
			}
		}
	}
}