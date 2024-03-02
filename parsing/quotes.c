/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:08:50 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/12 14:03:58 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_bool	check_quotes(char *cmd_line)
{
	int		i;
	int		len;
	char	quo_char;
	t_bool	quo_trigger;
	
	i = -1;
	quo_trigger = FALSE;
	quo_char = '\0';
	len = ft_strlen(cmd_line);
	while (++i < len)
	{
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_trigger = TRUE;
			quo_char = cmd_line[i];
			while (++i < len)
			{
				if (cmd_line[i] == quo_char)
				{
					quo_trigger = FALSE;
					quo_char = '\0';
					break;
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:08:50 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/17 18:25:16 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	init_vars(t_var *var, char *str)
{
	var->i = -1;
	var->qutrg = FALSE;
	var->qchr = '\0';
	var->len = ft_strlen(str);
}

t_bool	pass_consqut(char *str, t_var *var)
{
	if (((str[var->i] == '"' && str[var->i + 1] == '"') \
	|| (str[var->i] == '\'' && str[var->i + 1] == '\'')) \
	&& !var->qutrg)
	{
		var->i++;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	check_quotes(char *str)
{
	t_var	var;

	var = (t_var){0};
	init_vars(&var, str);
	while (++var.i < var.len)
	{
		if (pass_consqut(str, &var))
			continue ;
		if ((str[var.i] == '\'' || str[var.i] == '"') && !var.qutrg)
		{
			var.qutrg = TRUE;
			var.qchr = str[var.i];
			while (++var.i < var.len)
			{
				if (str[var.i] == var.qchr)
				{
					var.qutrg = FALSE;
					var.qchr = '\0';
					break ;
>>>>>>> main
				}
			}
		}
	}
<<<<<<< HEAD
	return (quo_trigger);
}

void	remove_cmdline_quotes(char *cmd_line, char **ret, int char_num)
{
	int	i;
	int	k;
	int trigger;
	int	len;

	i = -1;
	k = -1;
	len = (int)ft_strlen(cmd_line);
	*ret = malloc(sizeof(char) * (char_num + 1));
	while (++i < len)
	{
		if (cmd_line[i] == '\'' || cmd_line[i] == '"')
		{
			trigger = (int)cmd_line[i];
			while (++i < len)
			{
				if (cmd_line[i] == trigger)
					break;
				(*ret)[++k] = cmd_line[i];
			}
		}
		if (cmd_line[i] != ' ' && cmd_line[i] != '\'' && cmd_line[i] != '"')
			(*ret)[++k] = cmd_line[i];
	}
	(*ret)[++k] = '\0';
}

// int main(void)
// {
// 	int	char_num = 0;
// 	char *ret;

// 	while(1)
// 	{
// 		char *input = readline("$ ");
// 		if (check_quotes(input))
// 			printf("Error\n");
// 		else
// 		{
// 			printf ("correct\n");
// 			// get_str_quotes(input, &ret, char_num);
// 			// printf("%s\n", ret);
// 			// free (ret);
// 		}
// 		printf("-----\n");
// 		free (input);
// 	}
//     return 0;
// }
		
=======
	return (var.qutrg);
}
>>>>>>> main
