/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:34:15 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/20 15:33:57 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

int	check_file_dir(char **filename)
{
	struct stat	path_stat;

	if (!ft_strcmp(filename[0], "README.md"))
		return (print_message(filename[0], ": Permission denied"), 126);
	if (((filename[0][0] == '.' && filename[0][1] == '/') \
	|| filename[0][0] == '/') && access(filename[0], F_OK) == 0)
	{
		if (stat(filename[0], &path_stat) != 0)
		{
			perror("stat");
			return (126);
		}
		if (access(filename[0], X_OK) != 0)
			print_message(filename[0], ": Permission denied");
		else if (S_ISDIR(path_stat.st_mode))
			print_message(filename[0], ": is a directory");
		return (126);
	}
	else if (((filename[0][0] == '.' && filename[0][1] == '/') \
	|| filename[0][0] == '/') && access(filename[0], F_OK) != 0)
		print_message(filename[0], ": No such file or directory");
	else
		print_message(filename[0], ": command not found");
	return (127);
}

int	check_exec_file(char **inputs, t_parse *data)
{
	int	ret;

	ret = 0;
	if (!check_exec(inputs, data))
	{
		ret = check_file_dir(inputs);
		if (ret == 126)
			return (126);
		else if (ret == 127)
			return (127);
	}
	return (0);
}
