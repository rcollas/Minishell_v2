/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:29:41 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/12 14:59:21 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_dash_n(t_var *var)
{
	int	i;

	i = 0;
	if (!var->list->next)
		return (0);
	if (var->list->next->content[i] == '-')
	{
		i++;
		while (var->list->next->content[i] == 'n')
		{
			if (var->list->next->content[i + 1] == '\0'
				|| var->list->next->content[i + 1] == ' ')
			{
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	ft_echo(t_var *var)
{
	t_list	*start;
	int		i;

	i = -1;
	start = var->list->next;
	if (is_dash_n(var) == TRUE)
		start = start->next;
	while (start)
	{
		printf("%s", start->content);
		if (start->next)
			printf(" ");
		start = start->next;
	}
	if (is_dash_n(var) == FALSE)
		printf("\n");
	return (0);
}
