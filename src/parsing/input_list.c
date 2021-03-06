/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:11:12 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/08 17:03:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_input	*ft_inptlast(t_input *input)
{
	if (!input)
		return (NULL);
	while (input)
	{
		if (input->next == NULL)
			return (input);
		input = input->next;
	}
	return (NULL);
}

void	input_add_back(t_input **ainpt, t_input *new)
{
	t_input	*last;

	if (!ainpt || !new)
		return ;
	if (*ainpt)
	{
		last = ft_inptlast(*ainpt);
		last->next = new;
	}
	else
		*ainpt = new;
}

void	init_input(t_var *var, char *split, char **content)
{
	int	len;

	var->s_quote = 0;
	var->d_quote = 0;
	len = get_string_len(split, var);
	var->s_quote = 0;
	var->d_quote = 0;
	*content = ft_trim(var, split, len);
}

int	handle_input(t_var *var, t_input *new, char **split_input)
{
	int		i;
	int		j;
	int		ret;
	char	*content;

	i = -1;
	j = 0;
	while (split_input[++i])
	{
		init_input(var, split_input[i], &content);
		ret = handle_redir(var, new, split_input, &i);
		if (ret == 0 || ret == 1 || ret == 2)
		{
			ft_free(content);
			continue ;
		}
		else if (i == 0 || ((new->in_fd > 0 || new->out_fd > 0
					|| new->heredoc) && new->cmd == NULL))
			new->cmd = content;
		new->args[j++] = content;
		if (content == NULL)
			j--;
	}
	new->next = NULL;
	return (0);
}
