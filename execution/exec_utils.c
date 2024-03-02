/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:26:06 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/21 13:46:00 by habu-zua         ###   ########.fr       */
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:26:06 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/19 16:47:13 by alsaeed          ###   ########.fr       */
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
	free(str);
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

<<<<<<< HEAD
int		check_exec_path(char **inputs, t_parse *data)
=======
int	check_exec_path(char **inputs, t_parse *data)
>>>>>>> main
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

<<<<<<< HEAD
int		check_exec(char **inputs, t_parse *data)
=======
int	check_exec(char **inputs, t_parse *data)
>>>>>>> main
{
	int			ret;
	struct stat	statounet;

	statounet.st_mode = 0;
	ret = 0;
	stat(inputs[0], &statounet);
<<<<<<< HEAD
	if (ft_strchr(inputs[0], '/') && (statounet.st_mode & S_IXUSR) &&
	 !(statounet.st_mode & S_IFDIR))
=======
	if (ft_strchr(inputs[0], '/') && (statounet.st_mode & S_IXUSR)
		&& !(statounet.st_mode & S_IFDIR))
>>>>>>> main
		ret = 1;
	else
		ret = check_exec_path(inputs, data);
	return (ret);
<<<<<<< HEAD
}
=======
}

int	ft_strcmp1(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] > s2[i])
		return (1);
	else if (s1[i] < s2[i])
		return (-1);
	else
		return (0);
}
>>>>>>> main
