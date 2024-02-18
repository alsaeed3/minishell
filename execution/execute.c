/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:38:57 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/18 21:48:06 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static void	close_old_fds(t_parse *data)
{
	if (data->fds)
	{
		if (data->fds->oldfd[0])
			close(data->fds->oldfd[0]);
		if (data->fds->oldfd[1])
			close(data->fds->oldfd[1]);
	}
}

int	handle_exec(char **inputs, t_parse *data)
{
    int		ret;
    pid_t	pid;
	struct stat path_stat;

    ret = 0;
    if (!check_exec(inputs, data))
    {
        if (((inputs[0][0] == '.' && inputs[0][1] == '/') || inputs[0][0] == '/') \
        && access(inputs[0], F_OK) == 0)
		{
            if (stat(inputs[0], &path_stat) != 0)
			{
                perror("stat");
                return (126);
            }
            if (access(inputs[0], X_OK) != 0)
                print_message(inputs[0], ": Permission denied");
            else if (S_ISDIR(path_stat.st_mode))
                print_message(inputs[0], ": Is a directory");
            return (126);
        }
        else if (((inputs[0][0] == '.' && inputs[0][1] == '/') || inputs[0][0] == '/') \
        && access(inputs[0], F_OK) != 0)
            print_message(inputs[0], ": No such file or directory");
        else
            print_message(inputs[0], ": command not found");
		return (127);
    }
	g_signal = 3;
	pid = fork();
	if (pid == 0)
	{
		close_old_fds(data);
		if (execute(inputs, data) != 0)
			free_close_fd(data, 1, errno, NULL);
		free_close_fd(data, 0, 0, NULL);
	}
	else if (pid < 0)
		free_close_fd(data, 1, errno, NULL);
	else
		waitpid(pid, &ret, 0);
	if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	return (ret);
}

int	execute(char **inputs, t_parse *data)
{
	int	index;

	index = var_index("PATH=", data);
	if (ft_strchr(inputs[0], '/') && (access(inputs[0], X_OK) == 0))
	{
		if (data->fds->pfd[0])
		{
			close(data->fds->pfd[0]);
			data->fds->pfd[0] = 0;
		}
		if (data->fds->pfd[1])
		{
			close(data->fds->pfd[1]);
			data->fds->pfd[1] = 0;
		}
		if (execve(inputs[0], &inputs[0], data->env) != -1)
			return (0);
	}
	else if (index >= 0)
	{
		if (!execute_2(inputs, data))
			return (0);
	}
	return (1);
}

int	execute_2(char **inputs, t_parse *data)
{
	int			i;
	char		**paths;
	int			index;

	if (data->fds->oldfd[0])
		close(data->fds->oldfd[0]);
	if (data->fds->oldfd[1])
		close(data->fds->oldfd[1]);
	if (data->fds->pfd[0])
		close(data->fds->pfd[0]);
	if (data->fds->pfd[1])
		close(data->fds->pfd[1]);
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
