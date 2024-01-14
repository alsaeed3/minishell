/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:34:20 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/14 17:59:55 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/exec.h"
# define FORKED_CHILD 0

int		handle_basic(char **inputs,t_parse *parse, int piped);
void	choose_action(char **inpts,t_parse *data);
void	handle_exec(char **inputs, t_parse *data);
static int		handle_pipe(t_parse *parse);
int		check_exec(char **inputs, t_parse *data);
char	**gen_paths(int index, t_parse *data, char *input);
void	close_fds(t_parse *data);
void	exit_pipe(t_parse *data);
// void	error_sentence(char *str, int status);
int		execute_2(char **inputs, t_parse *data);
int		execute(char **inputs, t_parse *data);
int		check_exec_path(char **inputs, t_parse *data);
// int		var_index(char *name, t_parse *data);


void exec_delegator(t_parse *parser)
{
	if (parser->parts_num == 1)
		handle_basic(parser->cmds[0],parser, 0);
	else
        handle_pipe(parser);
}


int			handle_basic(char **inputs, t_parse *data, int piped)
{
	printf("handle_basic\n");
	// (void)input;
	// char	**inputs;
	int		oldfd[2];

	// inputs = data.cmds[0];
	oldfd[0] = dup(1);
	oldfd[1] = dup(0);
	choose_action(inputs,data);
	// free_inputs(inputs);
	dup2(oldfd[0], 1);
	dup2(oldfd[1], 0);
	close_fds(data);
	close(oldfd[0]);
	close(oldfd[1]);
	if (piped)
		exit_pipe(data);
	return (0);
}


void		choose_action(char **inputs,t_parse *data)
{
	printf("choose_action\n");
	if (!data->redir)
	{
		data->redir = 1;
		return ;
	}
	if (!ft_strcmp(inputs[0], "echo"))
		handle_echo(inputs);
	else if (!ft_strcmp(inputs[0], "pwd"))
		handle_pwd(data);
	else if (!ft_strcmp(inputs[0], "cd"))
		handle_cd(inputs, data);
	else if (!ft_strcmp(inputs[0], "env"))
		handle_env(data->env);
	else if (!ft_strcmp(inputs[0], "exit"))
		handle_exit(inputs, data);
	else if (!ft_strcmp(inputs[0], "export"))
		handle_export(inputs, data);
	else if (!ft_strcmp(inputs[0], "unset"))
		handle_unset(inputs, data);
	else
	{
		handle_exec(inputs, data);
	}
}

void	handle_exec(char **inputs, t_parse *data)
{
	printf("handle_exec\n");
	pid_t	pid;
	int		status;

	status = 0;
	if (!check_exec(inputs, data)) 
		return (error_sentence("\t\tminishell: Unknown command\n", 127));
	pid = fork();
	if (pid == 0)
	{
		if (execute(inputs, data) != 0)
			exit(errno);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		// sig_exec_init();
		waitpid(pid, &status, 0);
	}
	// g_status = WEXITSTATUS(status);
	// if (g_quit)
	// 	g_status = 130;
}

int		check_exec(char **inputs, t_parse *data)
{
	int			ret;
	struct stat	statounet;

	statounet.st_mode = 0;
	ret = 0;
	stat(inputs[0], &statounet);
	if (ft_strchr(inputs[0], '/') && (statounet.st_mode & S_IXUSR) &&
	 !(statounet.st_mode & S_IFDIR))
		ret = 1;
	else
		ret = check_exec_path(inputs, data);
	return (ret);
}

int		check_exec_path(char **inputs, t_parse *data)
{
	int			i;
	int			index;
	char		**paths;
	struct stat	statounet;

	statounet.st_mode = 0;
	i = 0;
	index = var_index("PATH=", data);
	if (var_index("PATH=", data) == -1)
		return (0);
	index = var_index("PATH=", data);
	paths = gen_paths(index, data, inputs[0]);
	while (paths[i])
	{
		stat(paths[i], &statounet);
		if ((statounet.st_mode & S_IXUSR) && !(statounet.st_mode & S_IFDIR))
		{
			// free_env(paths);
			return (1);
		}
		i++;
	}
	// free_env(paths);
	return (0);
}


char	**gen_paths(int index, t_parse *data, char *input)
{
	char	*str;
	char	**paths;
	char	*temp;
	int		i;

	i = 0;
	str = ft_strdup(&data->env[index][5]);
	paths = ft_split(str, ':');
	free(str);
	while (paths[i])
	{
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(temp);
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], input);
		free(temp);
		i++;
	}
	return (paths);
}

static int handle_pipe(t_parse *parser)
{
    int i = 0;
    int fds[2];
    int pid;
    int status;
    int fd_in = 0;
    // char *path;
    printf("parts_num: %d\n", parser->parts_num);
    while (i < parser->parts_num)
    {
        if(i < parser->parts_num - 1)
            pipe(fds);
        pid = fork();
        if (pid == -1)
            exit(EXIT_FAILURE);
        else if (pid == FORKED_CHILD)
        {
            dup2(fd_in, STDIN_FILENO);
            if (i < parser->parts_num - 1)
                dup2(fds[STDOUT_FILENO], STDOUT_FILENO);
            close(fds[0]);
            // pipe_exec(parser.cmds[i]);
			handle_basic(parser->cmds[i],parser, 1);
			/*
            path = ft_getpath(parser.cmds[i][0], getenv("PATH"));
            execve(path, parser.cmds[i], NULL);
            exit(126);
			*/
        }
        waitpid(pid, &status, 0);
        printf("status: %d\n", WEXITSTATUS(status));
        close(fds[1]);
        fd_in = fds[0];
        i++;
    }
    return 0;
}


void		close_fds(t_parse *data)
{
	if (data->fd_in != 0)
	{
		close(data->fd_in);
		data->fd_in = 0;
	}
	if (data->fd_out != 1)
	{
		close(data->fd_out);
		data->fd_out = 1;
	}
}

void		exit_pipe(t_parse *data)
{
	// free_inputs(data->env);
	// if (g_user_input)
	// 	free(g_user_input);
	free(data->pwd);
	exit(EXIT_SUCCESS);
}

int		execute(char **inputs, t_parse *data)
{
	int			index;
	struct stat	statounet;

	statounet.st_mode = 0;
	index = var_index("PATH=", data);
	stat(inputs[0], &statounet);
	if (ft_strchr(inputs[0], '/') && (statounet.st_mode & S_IXUSR) &&
	(execve(inputs[0], &inputs[0], data->env) != -1))
		return (0);
	else if (index >= 0)
	{
		if (!execute_2(inputs, data))
			return (0);
	}
	return (1);
}

int		execute_2(char **inputs, t_parse *data)
{
	int			i;
	char		**paths;
	int			index;
	struct stat	statounet;

	i = 0;
	statounet.st_mode = 0;
	index = var_index("PATH=", data);
	paths = gen_paths(index, data, inputs[0]);
	while (paths[i])
	{
		stat(paths[i], &statounet);
		if ((statounet.st_mode & S_IXUSR) &&
		(execve(paths[i], inputs, data->env) != -1))
			return (0);
		i++;
	}
	// free_env(paths);
	return (1);
}

// int		var_index(char *name, t_parse *data)
// {
// 	int		y;
// 	int		x;

// 	x = 0;
// 	while (data->env[x])
// 	{
// 		y = 0;
// 		while (data->env[x][y] && data->env[x][y] == name[y]
// 		&& name[y] != '\0' && name[y] != '=' &&
// 		data->env[x][y] != '\0' && data->env[x][y] != '=')
// 			y++;
// 		if ((data->env[x][y] == '\0' || data->env[x][y] == '=') &&
// 		(name[y] == '\0' || name[y] == '='))
// 			return (x);
// 		x++;
// 	}
// 	return (-1);
// }

void	handle_echo(char **args)
{
	printf("handle_echo\n");
	int i;
	int n_flag;

	i = 1;
	n_flag = 0;
	g_status = 0;
	while (args[i] && !ft_strcmp(args[i], "-n") && i++)
		n_flag = 1;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
}

void	handle_pwd(t_parse *data)
{
	printf("handle_pwd\n");
	ft_putstr(data->pwd);
	ft_putstr("\n");
	g_status = 0;
}
