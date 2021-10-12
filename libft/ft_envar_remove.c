/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envar_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:42:33 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/12 14:42:48 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	envar_remove(t_envar **envar, int pos)
{
	t_envar	*start;
	t_envar	*tmp;
	int		i;

	start = *envar;
	i = 0;
	if (pos < 1 || pos > ft_envarsize(*envar))
		return (0);
	while (*envar && ++i < pos - 1)
	{
		*envar = (*envar)->next;
	}
	if (i == 1)
		*envar = (*envar)->next;
	else
	{
		tmp = (*envar)->next;
		if ((*envar)->next->next)
			(*envar)->next = (*envar)->next->next;
		else
			(*envar)->next = NULL;
		free(tmp);
		*envar = start;
	}
	return (1);
}
