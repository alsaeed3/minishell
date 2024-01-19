/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:34:20 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/19 19:31:23 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	choose_action(char **inpts,t_parse *data);
void	handle_exec(char **inputs, t_parse *data);
int		execute_2(char **inputs, t_parse *data);
int		execute(char **inputs, t_parse *data);

void 	exec_delegator(t_parse *parser)
{
	if (parser->parts_num == 1)
		handle_basic(parser->cmds[0],parser, 0, 0);
	else
        handle_pipe(parser);
}


int		handle_basic(char **inputs, t_parse *data, int piped, int x)
{
	printf("handle_basic\n");
	int		oldfd[2];

	oldfd[0] = dup(1);
	oldfd[1] = dup(0);
	printf("dats->in_redir_num[0]: %d\n", data->in_redir_num[0]);
	if(data->out_redir_num[x]>0)
		redirect_to(inputs,data, x);
	else if(data->in_redir_num[x]> 0)
		redirect_from(inputs,data, x);
	choose_action(inputs,data);
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
