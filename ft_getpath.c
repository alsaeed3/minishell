/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:48:43 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/05 16:55:27 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/main.h"

char *ft_getpath(char *cmd, char *envpath)
{
    int i;
    char **temp;
    char *path;
    char *temp2;
	
	if(access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
 
    temp = ft_split(envpath, ':');
    i = 0;
    while(temp[i])
    {
        temp2 = ft_strjoin(temp[i], "/");
        path = ft_strjoin(temp2, cmd);
        free(temp2);
        if (access(path, F_OK) == 0)
		{
			// printf("path = %s\n", path);
			return (ft_free(temp), path);
		}
        free(path);
        i++;
    }
	ft_free(temp);
    return (NULL);
}