/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:05:52 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/11 23:21:48 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	**gen_paths(int index, t_data *data, char *input)
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

int		check_exec_path(char **inputs, t_data *data)
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
			free_env(paths);
			return (1);
		}
		i++;
	}
	free_env(paths);
	return (0);
}

int		check_exec(char **inputs, t_data *data)
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
