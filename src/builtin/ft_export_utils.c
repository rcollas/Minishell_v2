/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:07:27 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/26 11:32:02 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cmd_export_alone(t_var *var)
{
	t_envar	*tmp2;

	tmp2 = var->export;
	if (var->input->args[1] == 0)
	{
		while (tmp2)
		{
			if (tmp2->content == 0)
			{
				printf("export %s\n", tmp2->name);
			}
			if (tmp2->content != 0)
			{
				printf("export %s=\"%s\"\n", tmp2->name, tmp2->content);
			}
			tmp2 = tmp2->next;
		}
		return (1);
	}
	return (0);
}

char	*export_name_equal_search(char *str, int *i, int *equal, char *name)
{
	while (str[(*i)])
	{
		if (str[(*i)] == '=')
		{
			(*equal) = 1;
			break ;
		}
		name[(*i)] = str[(*i)];
		(*i)++;
	}
	name[(*i)] = 0;
	return (name);
}

char	*export_content_search(int *i, char *str, char *content)
{
	int	j;

	j = 0;
	while (str[(*i)])
	{
		content[j] = str[(*i)];
		j++;
		(*i)++;
	}
	content[j] = 0;
	return (content);
}

int	cmd_export_insert(t_var *var, char *name, char *content)
{
	t_envar	*new;
	t_envar	*tmp2;
	int		pos;

	tmp2 = var->export;
	if (var->equal_env == 0)
	{
		new = ft_envar_new(name, 0);
		pos = ft_envarsize(tmp2);
		envar_insert(&var->export, new, pos);
	}
	else
	{
		new = ft_envar_new(name, content);
		pos = ft_envarsize(tmp2);
		envar_insert(&var->export, new, pos);
	}
	return (0);
}
