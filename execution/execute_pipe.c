/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:01:20 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/13 22:09:17 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

// int	handle_single_pipe(char **inputs, t_parse *data, int x)
// {
// 	int	ret;

// 	expand_dolar_sign(inputs, data);
// 	ret = 0;
// 	if (data->in_rdr_num[x] > 0)
// 		if (redirect_from(data, x))
// 			return (1);
// 	if (data->out_rdr_num[x] > 0)
// 	{
// 		ret = redirect_to(data, x);
// 		if (ret == 127)
// 			return (127);
// 		else if (ret == 1)
// 			return (0);
// 	}
// 	ret = choose_action_pipe(inputs, data, x);
// 	close_fds(data);
// 	return (ret);
// }

// int	handle_single_pipe(char **inputs, t_parse *data, int x)
// {
// 	int fd;
//     char *filename;
// 	int	ret;
// 	int i;

// 	expand_dolar_sign(inputs, data);
// 	ret = 0;
// 	if (data->in_rdr_num[x] > 0)
// 	{
// 		filename = get_file_name(data, x);
// 		if (!filename)
// 			return 1;

// 		fd = open(filename, O_RDONLY);
// 		if (fd < 0) {
// 			ft_error(strerror(errno));
// 			return 2;
// 		}
// 		if (dup2(fd, 0) == -1) {
// 			ft_putendl_fd("dup2 failed", 2);
// 			close(fd);
// 			return 1;
// 		}
// 		close(fd);
// 		if (ret == 127)
// 			return (127);
// 		else if (ret == 1)
// 			return (0);
// 	}
// 	if (data->out_rdr_num[x] > 0)
// 	{
// 		i = 0;
// 		while (i < data->out_rdr_num[x]) 
// 		{
// 			filename = data->outputs_redirections[x][i];
// 			if (data->outputs_tokens[x][i] == 1)
// 				fd = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
// 			else
// 				fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
// 			if (fd < 0)
// 			{
// 				ft_putendl_fd("Error: wrong permissions", 2);
// 				return (127);
// 			}
// 			i++;
// 		}
// 		if (dup2(fd, 1) == -1) {
// 			ft_putendl_fd("dup2 failed", 2);
// 			close(fd);
// 			return (1);
// 		}
// 		close(fd);
// 	}
// 	if (ft_strcmp(inputs[0], "echo") == 0)
// 		handle_echo(data, x);
// 	else if (ft_strcmp(inputs[0], "pwd") == 0)
// 		handle_pwd(data);
// 	else if (ft_strcmp(inputs[0], "cd") == 0)
// 		handle_cd(inputs, data);
// 	else if (ft_strcmp(inputs[0], "env") == 0)
// 		handle_env(data->env);
// 	else if (ft_strcmp(inputs[0], "exit") == 0)
// 		handle_exit(inputs, data);
// 	else if (ft_strcmp(inputs[0], "export") == 0)
// 		ret = handle_export(inputs, data);
// 	else if (ft_strcmp(inputs[0], "unset") == 0)
// 		handle_unset(inputs, data);
// 	else
// 		ret = handle_exec_pipe(inputs, data);
// 	close_fds(data);
// 	return (ret);
// }

void handle_single_pipe(char **inputs, t_parse *data, t_pipe *pipes)
{
    char *filename;
    int fd;
    int ret = 0;

    expand_dolar_sign(inputs, data);
    // Input redirection
    if (data->in_rdr_num[pipes->i] > 0)
    {
        filename = get_file_name(data, pipes->i);
        if (!filename)
            free_close_fd(data, 0, 1);
        close(STDIN_FILENO);
        fd = open(filename, O_RDONLY);
        if (fd < 0)
        {
            perror("open input file");
            free(pipes->pipe_fds);
		    free (pipes->pid);
            free_close_fd(data, 0, 2);
        }
    }
    // Output redirection
    if (data->out_rdr_num[pipes->i] > 0)
    {
        for (int i = 0; i < data->out_rdr_num[pipes->i]; i++)
        {
            filename = data->outputs_redirections[pipes->i][i];
            int flags = O_RDWR | O_CREAT;
            if (data->outputs_tokens[pipes->i][i] == 1)
                flags |= O_APPEND;
            else
                flags |= O_TRUNC;
            close(STDOUT_FILENO);
            fd = open(filename, flags, S_IRUSR | S_IWUSR);
            if (fd < 0)
            {
                perror("open output file");
                free(pipes->pipe_fds);
	        	free (pipes->pid);
                free_close_fd(data, 0, 2);
            }
        }
    }
    // Handle built-in commands
    if (ft_strcmp(inputs[0], "echo") == 0)
        handle_echo(data, pipes->i);
    else if (ft_strcmp(inputs[0], "pwd") == 0)
        handle_pwd(data);
    else if (ft_strcmp(inputs[0], "cd") == 0)
        handle_cd(inputs, data);
    else if (ft_strcmp(inputs[0], "env") == 0)
        handle_env(data->env);
    else if (ft_strcmp(inputs[0], "exit") == 0)
        handle_exit(inputs, data);
    else if (ft_strcmp(inputs[0], "export") == 0)
        ret = handle_export(inputs, data);
    else if (ft_strcmp(inputs[0], "unset") == 0)
        handle_unset(inputs, data);
    else
        ret = handle_exec_pipe(inputs, data);
    // Close any remaining file descriptors
    close_fds(data);
    free(data->fds);
    free(pipes->pipe_fds);
	free (pipes->pid);
    free_close_fd(data, 0, ret);
}

int	choose_action_pipe(char **cmd, t_parse *data, int x)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd[0], "echo") == 0)
		handle_echo(data, x);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		handle_pwd(data);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		handle_cd(cmd, data);
	else if (ft_strcmp(cmd[0], "env") == 0)
		handle_env(data->env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		handle_exit(cmd, data);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ret = handle_export(cmd, data);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		handle_unset(cmd, data);
	else
		ret = handle_exec_pipe(cmd, data);
	return (ret);
}

int	handle_exec_pipe(char **inputs, t_parse *data)
{
	int		ret;

	ret = 0;
	if (!check_exec(inputs, data))
	{
		print_message(inputs[0], ": command not found");
		close_new_fd(data);
		return (127);
	}
	g_signal = 3;
	// close_new_fd(data);
	if (execute(inputs, data) != 0)
		free_close_fd(data, 0, errno);
	return (ret);
}

int	execute_pipe(char **inputs, t_parse *data)
{
	int			index;

	index = var_index("PATH=", data);
	if (ft_strchr(inputs[0], '/') && (access(inputs[0], X_OK) == 0))
	{
		if (execve(inputs[0], &inputs[0], data->env) != -1)
			return (0);
	}
	else if (index >= 0)
	{
		if (!execute_2_pipe(inputs, data))
			return (0);
	}
	return (1);
}

int	execute_2_pipe(char **inputs, t_parse *data)
{
	int			i;
	char		**paths;
	int			index;

	i = 0;
	index = var_index("PATH=", data);
	paths = gen_paths(index, data, inputs[0]);
	while (paths[i])
	{
		if (access(paths[i], X_OK) == 0
			&& execve(paths[i], &inputs[0], data->env) != -1)
			return (0);
		i++;
	}
	return (1);
}
