/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:13:53 by habu-zua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/31 20:53:33 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/15 14:09:46 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

char	**gen_paths(int index, t_parse *data, char *input)
{
	char	*str;
	char	**paths;
	char	*temp;
	int		i;

	i = 0;
	str = ft_strdup(&data->env[index][5]);
	paths = ft_split(str, ':');
<<<<<<< HEAD
	free (str);
	str = NULL;
=======
	free_set_null((void **)&str);
>>>>>>> main
	while (paths[i])
	{
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
<<<<<<< HEAD
		free(temp);
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], input);
		free(temp);
=======
		free_set_null((void **)&temp);
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], input);
		free_set_null((void **)&temp);
>>>>>>> main
		i++;
	}
	return (paths);
}

int	check_exec_path(char **inputs, t_parse *data)
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
