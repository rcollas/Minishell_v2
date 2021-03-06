/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envarsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:39:21 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/27 14:44:09 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_envarsize(t_envar *envar)
{
	int	i;

	i = 0;
	while (envar)
	{
		envar = envar->next;
		i++;
	}
	return (i);
}
