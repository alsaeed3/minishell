/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:13:53 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/19 19:14:17 by habu-zua         ###   ########.fr       */
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:13:53 by habu-zua          #+#    #+#             */
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
<<<<<<< HEAD
			// free_env(paths);
=======
			free_env(paths);
>>>>>>> main
			return (1);
		}
		i++;
	}
<<<<<<< HEAD
	// free_env(paths);
	return (0);
}
=======
	free_env(paths);
	return (0);
}
>>>>>>> main
