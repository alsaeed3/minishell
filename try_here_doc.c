#include "inc/exec.h"

// void	find_heredocs_num(t_parse **data)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < (*data)->parts_num)
// 	{
// 		j = -1;
// 		while (++j < (*data)->in_redir_num[i])
// 		{
// 			if ((*data)->inputs_tokens[i][j] == 1)
// 				(*data)->heredocs_num++;
// 		}
// 	}
// }

// char	find_heredocs_ends(t_parse **data)
// {
// 	int	i;
// 	int	j;
// 	int k;

// 	(*data)->heredocs_ends = ft_calloc(((*data)->heredocs_num) + 1, sizeof(char *));
// 	i = -1;
// 	k = 0;
// 	while ((*data)->inputs_redirections[++i])
// 	{
// 		j = -1;
// 		while ((*data)->inputs_redirections[i][++j] && k < ((*data)->heredocs_num))
// 		{
// 			if ((*data)->inputs_tokens[i][j] == 1)
// 				(*data)->heredocs_ends[k++] = ft_strdup((*data)->inputs_redirections[i][j]);
// 		}
// 	}
// 	(*data)->heredocs_ends[k] = NULL;
// }

char	**try_heredoc(char **heredocs_ends)
{
    char	*line;
    int		tempFile;
	char	**heredoc_line;
	char	*tmp;
	int		i;
	int		heredocs_num;

	heredoc_line = NULL;
	heredocs_num = ft_array_size(heredocs_ends);
	heredoc_line = ft_calloc(heredocs_num + 1, sizeof(char *));
    // Open a temporary file for writing
	i = -1;
    while (++i < heredocs_num)
	{
		tempFile = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tempFile == -1) {
			perror("Error opening temporary file");
			return (NULL);
		}
		// Read lines from the user until the end marker is entered
		while (1) 
		{
			line = readline("> ");
			if (line == NULL || line[0] == '\0' || ft_strcmp(line, heredocs_ends[i]) == 0) {
				free(line);
				break;
			}
			// Write the line to the temporary file
			write(tempFile, line, ft_strlen(line));
			write(tempFile, "\n", 1);
			free(line);
		}
		// Close the temporary file
		close(tempFile);
		// Open the temporary file for reading
		tempFile = open("temp.txt", O_RDONLY);
		if (tempFile == -1) 
		{
			perror("Error opening temporary file");
			return (NULL);
		}
		// Read the heredoc content from the temporary file
		line = get_next_line(tempFile);
		while (line) 
		{
			tmp = ft_strjoin(heredoc_line[i], line);
			if (!tmp)
			{
				free(line);
				free(heredoc_line[i]);
				return NULL;
			}
			free(heredoc_line[i]);
			heredoc_line[i] = tmp;
			free(line);
			line = get_next_line(tempFile);
		}
    	close(tempFile);
		if (unlink("temp.txt") != 0)
		{
			perror("Error deleting temporary file");
			return (NULL);
		}
	}
	heredoc_line[i] = NULL;
    // Close the temporary file
    // Delete the temporary file
    return (heredoc_line);
}

// int main(int argc, char **argv)
// {
// 	char **heredoc_line;
// 	int		i;
// 	int		size;

//     if (argc < 2) {
//         fprintf(stderr, "Usage: %s end_marker\n", argv[0]);
//         return 1;
//     }
// 	heredoc_line = NULL;
// 	heredoc_line = try_heredoc(argv);
// 	replace_heredoc( heredoc_line);
// 	size = ft_array_size(heredoc_line);
// 	i = -1;
// 	printf("------------------\n");
// 	while (++i < size)
// 	{
// 		printf("%s", heredoc_line[i]);
// 		printf("...............\n");
// 	}
// 	return 0;
// }

// void	find_heredocs_num(t_parse **data)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < (*data)->parts_num)
// 	{
// 		j = -1;
// 		while (++j < (*data)->in_redir_num[i])
// 		{
// 			if ((*data)->inputs_tokens[i][j] == 1)
// 				(*data)->heredocs_num++;
// 		}
// 	}
// }

// void	find_heredocs_ends(t_parse **data)
// {
// 	int	i;
// 	int	j;
// 	int k;

// 	(*data)->heredocs_ends = ft_calloc(((*data)->heredocs_num) + 1, sizeof(char *));
// 	i = -1;
// 	k = 0;
// 	while ((*data)->inputs_redirections[++i])
// 	{
// 		j = -1;
// 		while ((*data)->inputs_redirections[i][++j] && k < ((*data)->heredocs_num))
// 		{
// 			if ((*data)->inputs_tokens[i][j] == 1)
// 				(*data)->heredocs_ends[k++] = ft_strdup((*data)->inputs_redirections[i][j]);
// 		}
// 	}
// 	(*data)->heredocs_ends[k] = NULL;
// }

// void	handle_heredoc_last(t_parse **data)
// {
//     char	*line;
//     int		*tempFiles;
// 	char	**heredoc_line;
// 	char	*tmp;
// 	int		i;
	
// 	heredoc_line = NULL;
//     // Open a temporary file for writing
// 	i = -1;
//     while (++i < (*data)->heredocs_num)
// 	{
// 		tempFiles[i] = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (tempFiles[i] == -1) {
// 			perror("Error opening temporary file");
// 			return (NULL);
// 		}
// 		// Read lines from the user until the end marker is entered
// 		while (1) 
// 		{
// 			line = readline("> ");
// 			if (line == NULL || line[0] == '\0' || ft_strcmp(line,(*data)->heredocs_ends[i]) == 0) {
// 				free(line);
// 				break;
// 			}
// 			// Write the line to the temporary file
// 			write(tempFiles[i], line, ft_strlen(line));
// 			write(tempFiles[i], "\n", 1);
// 			free(line);
// 		}
// 		// Close the temporary file
// 		close(tempFiles[i]);
// 		// Open the temporary file for reading
// 		tempFiles[i] = open("temp.txt", O_RDONLY);
// 		if (tempFiles[i] == -1) 
// 		{
// 			perror("Error opening temporary file");
// 			return (NULL);
// 		}
// 		// Read the heredoc content from the temporary file
// 		line = NULL;
// 		line = get_next_line(tempFiles[i]);
// 		while (line) 
// 		{
// 			tmp = ft_strjoin(heredoc_line[i], line);
// 			if (!tmp)
// 			{
// 				free(line);
// 				free(heredoc_line);
// 				return NULL;
// 			}
// 			free(heredoc_line[i]);
// 			heredoc_line = tmp;
// 			free(line);
// 			line = get_next_line(tempFiles[i]);
// 		}
//     	close(tempFiles[i]);
// 		if (unlink("temp.txt") != 0)
// 		{
// 			perror("Error deleting temporary file");
// 			return (NULL);
// 		}
// 	}
//     // Close the temporary file
//     // Delete the temporary file
//     return (heredoc_line);
// }