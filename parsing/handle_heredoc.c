/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:16:57 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/24 12:27:17 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	find_heredocs_num(t_parse *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->inputs_redirections[++i])
	{
		j = -1;
		while (data->inputs_redirections[i][++j])
		{
			if (data->inputs_redirections[i][j + 1] == NULL && data->inputs_tokens[i][j] == 1)
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

void	handle_heredoc(t_parse *data)
{
    char	*line;
    int		tmp_fd;
	int		i;
	int		j;
	int		k;

	data->heredoc_tmp_files = ft_calloc(data->heredocs_num + 1, sizeof(char *));
	if (!data->heredoc_tmp_files)
		return ;
	// heredoc_line = ft_calloc((data->heredocs_num) + 1, sizeof(char *));
    // Open a temporary file for writing
	printf("\n");
	printf("heredocs_num\n");
	printf("%d\n", data->heredocs_num);
	printf("\n");
	k = 0;
	i = -1;
	while (data->inputs_redirections[++i])
	{
		j = -1;
		while (data->inputs_redirections[i][++j])
		{
			if (data->inputs_redirections[i][j + 1] != NULL && data->inputs_tokens[i][j] == 1)
			{
				while (1) 
				{
					line = readline("> ");
					if (line == NULL || line[0] == '\0' || ft_strcmp(line, data->inputs_redirections[i][j]) == 0)
					{
						free(line);
						break;
					}
				}
			}
			else if (data->inputs_redirections[i][j + 1] == NULL && data->inputs_tokens[i][j] == 1)
			{
				data->heredoc_tmp_files[k] = generate_file_names(k + 1);
				tmp_fd = open(data->heredoc_tmp_files[k++], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				printf("%d\n", tmp_fd);
				if (tmp_fd == -1)
				{
					perror("Error opening temporary file");
					free (data->heredoc_tmp_files);
					return ;
				}
				// Read lines from the user until the end marker is entered
				while (1) 
				{
					line = readline("> ");
					if (line == NULL || line[0] == '\0' || ft_strcmp(line, data->inputs_redirections[i][j]) == 0)
					{
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
			//	------------------------------------------------------------------
			}
		}
	}
	printf("i: %d\n", i);
	if (data->heredocs_num)
		data->heredoc_tmp_files[k] = NULL;
}
    // Close the temporary file
    // Delete the temporary file
    // data->hd_usr_input = heredoc_line;
	// replace_heredoc(data);
	//	------------------------------------------------------------------

void	read_heredocs(t_parse *data)
{
	char	*line;
	char	**heredoc_line;
	char	*tmp;
	int		tmp_fd;
	int		i;

	heredoc_line = ft_calloc(data->heredocs_num + 1, sizeof(char *));
	// Open the temporary file for reading
	i = -1;
	while (++i < data->heredocs_num)
	{
		tmp_fd = open(data->heredoc_tmp_files[i], O_RDONLY);
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
				break ;
			}
			// free(heredoc_line[i]);
			heredoc_line[i] = ft_strdup(tmp);
			free(line);
			free(tmp);
			line = get_next_line(tmp_fd);
		}
		close(tmp_fd);
		if (unlink(data->heredoc_tmp_files[i]) != 0)
		{
			perror("Error deleting temporary file");
			return ;
		}
	}
	heredoc_line[i] = NULL;
	printf("heredoc_lines:\n");
	i = -1;
	while (++i < data->heredocs_num)
		printf("%s\n", heredoc_line[i]);
	printf("heredoc_lines:\n");
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