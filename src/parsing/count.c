/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:57:30 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/08 17:03:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_pipes(t_var *var)
{
	int	i;
	int	pipe_count;
	int	s_quote;
	int	d_quote;

	i = -1;
	pipe_count = 1;
	s_quote = 0;
	d_quote = 0;
	while (var->cmd[++i])
	{
		if (var->cmd[i] == '"' && s_quote == FALSE)
			check_d_quote(&d_quote);
		if (var->cmd[i] == '\'' && d_quote == FALSE)
			check_s_quote(&s_quote);
		if (var->cmd[i] == '|' && s_quote == FALSE && d_quote == FALSE)
			pipe_count++;
	}
	return (pipe_count);
}

int	split_len(char **split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (split[i])
	{
		if (ft_strcmp(split[i], ">") == 1)
			i += 2;
		else if (ft_strcmp(split[i], ">>") == 1)
			i += 2;
		else if (ft_strcmp(split[i], "<") == 1)
			i += 2;
		else if (ft_strcmp(split[i], "<<") == 1)
			i += 2;
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

int	count_heredoc(char **split_input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (split_input[i])
	{
		if (ft_strcmp(split_input[i], "<<") == TRUE)
		{
			i += 2;
			count += 2;
		}
		else
			i++;
	}
	return (count);
}
