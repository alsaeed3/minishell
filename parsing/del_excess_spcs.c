/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_excess_spcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:24:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/12 17:27:53 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static void	jump_over_spaces(char *cmd_line, int *i)
{
	(*i)++;
	while (cmd_line[*i] == ' ')
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:24:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/20 17:50:38 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	jump_over_spaces(char *str, int *i)
{
	(*i)++;
	while (str[*i] == ' ')
>>>>>>> main
		(*i)++;
	(*i)--;
}

<<<<<<< HEAD
static int size_without_spcs(char *cmd_line)
{
	int		i;
	int		len;
	t_bool	quo_trigger;
	char	quo_char;
	int		size;

	len = ft_strlen(cmd_line);
	i = -1;
	size = 0;
	if (cmd_line[0] == ' ')
			jump_over_spaces(cmd_line, &i);
	quo_trigger = FALSE;
	while (++i < len)
	{
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_trigger = TRUE;
			quo_char = cmd_line[i];
		}
		else if (cmd_line[i] == quo_char && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (cmd_line[i] == ' ' && cmd_line[i + 1] == ' ' && !quo_trigger)
		{
			size++;
			while (cmd_line[i] == ' ')
				i++;
			if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
			{
				quo_trigger = TRUE;
				quo_char = cmd_line[i];
			}
		}
		size++;
	}
	return (size);
}

char	*delete_excess_spcs(char *cmd_line)
{
	int		i;
	int		j;
	int		len;
	t_bool	quo_trigger;
	char	quo_char;
	int		size;
	char	*ret;

	len = ft_strlen(cmd_line);
	size = size_without_spcs(cmd_line);
	ret = ft_calloc(size + 1, sizeof(char));
	j = 0;
	i = -1;
	quo_trigger = FALSE;
	if (cmd_line[0] == ' ')
			jump_over_spaces(cmd_line, &i);
	while (++i < len)
	{
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_trigger = TRUE;
			quo_char = cmd_line[i];
		}
		else if (cmd_line[i] == quo_char && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (cmd_line[i] == ' ' && cmd_line[i + 1] == ' ' && !quo_trigger)
		{
			ret[j++] = cmd_line[i];
			while (cmd_line[i] == ' ')
				i++;
			if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
			{
				quo_trigger = TRUE;
				quo_char = cmd_line[i];
			}
		}
		ret[j++] = cmd_line[i];
	}
	ret[j] = '\0';
	return (ret);
}

/* To test delete_excess_spcs function */
// int main(void)
// {
// 	int	i;
// 	char *str;
// 	while(1)
// 	{
// 		char *input = readline("$> ");
// 		// char *input = "  <  '1     23'  |  << '  12 ' ";
// 		str = delete_excess_spcs(input);
// 		free(input);
// 		printf("%s\n",str);
// 		free(str);
// 	}
// }

/* To test size_without_spcs function */
// int main(void)
// {
// 	int	i;
// 	int size;
// 	size = 0;
// 	while(1)
// 	{
// 		char *input = readline("$> ");
// 		size = size_without_spcs(input);
// 		free(input);
// 		printf("%d\n",size);
// 	}
// }
=======
static t_bool	delco_consqut(char *str, t_var *var)
{
	if (((str[var->i] == '"' && str[var->i + 1] == '"') \
	|| (str[var->i] == '\'' && str[var->i + 1] == '\'')) \
	&& !var->qutrg)
	{
		var->size += 2;
		var->i++;
		return (TRUE);
	}
	return (FALSE);
}

void	jmp_mid_spcs(t_var *var, char *str, int mode)
{
	if (str[var->i] == ' ' && str[var->i + 1] == ' ' && !var->qutrg)
	{
		if (mode == 0 && str[var->i] != ' ' && (var->i < var->len - 1 \
		|| (var->i == var->len - 1 && str[var->len - 1] != ' ')))
			var->size++;
		else if (mode == 1 && str[var->i] != ' ' && (var->i < var->len - 1 \
		|| (var->i == var->len - 1 && str[var->len - 1] != ' ')))
			var->ret[var->j++] = str[var->i];
		var->i++;
	}
	if (str[var->i] == ' ' && !var->qutrg)
	{
		if (mode == 0)
			var->size++;
		else if (mode == 1)
			var->ret[var->j++] = str[var->i++];
	}
	while (str[var->i] == ' ' && !var->qutrg)
		var->i++;
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->qutrg = TRUE;
		var->qchr = str[var->i];
	}
}

int	size_without_spcs(char *str)
{
	t_var	var;

	var = (t_var){0};
	init_del_exspc(&var, str, 0);
	while (++var.i < var.len)
	{
		if (delco_consqut(str, &var))
			continue ;
		if ((str[var.i] == '\'' || str[var.i] == '"') && !var.qutrg)
		{
			var.qutrg = TRUE;
			var.qchr = str[var.i];
		}
		else if (str[var.i] == var.qchr && var.qutrg)
		{
			var.qchr = '\0';
			var.qutrg = FALSE;
		}
		jmp_mid_spcs(&var, str, 0);
		if (var.i < var.len - 1 || (var.i == var.len - 1 \
		&& str[var.len - 1] != ' '))
			var.size++;
	}
	return (var.size);
}

char	*delete_excess_spcs(char *str)
{
	t_var	var;

	var = (t_var){0};
	init_del_exspc(&var, str, 1);
	while (++var.i < var.len)
	{
		if (del_consqut(str, &var))
			continue ;
		jmp_mid_spcs(&var, str, 1);
		if (var.i < var.len - 1 || (var.i == var.len - 1 \
		&& str[var.len - 1] != ' '))
			var.ret[var.j++] = str[var.i];
	}
	if (var.ret[var.j] == ' ')
		var.ret[var.j] = '\0';
	else if (var.ret[var.j])
		var.ret[++var.j] = '\0';
	free_set_null((void **)&str);
	return (var.ret);
}
>>>>>>> main
