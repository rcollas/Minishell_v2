/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:57:53 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/08 17:03:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*delete_last_line(char *str)
{
	int		i;
	char	*final_str;

	if (str == NULL)
		return (NULL);
	i = ft_strlen(str) - 2;
	while (i >= 1 && str[i - 1] != '\n')
		i--;
	final_str = malloc(sizeof(char) * (i + 1));
	if (final_str == 0)
		return (NULL);
	final_str[i] = 0;
	while (--i >= 0)
		final_str[i] = str[i];
	free (str);
	return (final_str);
}

char	*trim_heredoc(char *str, int len, t_var *var)
{
	char	*trim_str;
	char	*tmp;
	int		i;
	int		j;

	trim_str = ft_calloc(sizeof(char), (len + 1));
	if (!trim_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[j] == '$' && ft_isalnum(str[j + 1]) && var->expand)
		{
			j++;
			tmp = get_valid_envar(var, str, j);
			assign_envar(tmp, trim_str, &i);
			skip_alnum(str, &j);
			continue ;
		}
		trim_str[i++] = str[j++];
	}
	free (str);
	var->expand = 1;
	return (trim_str);
}

void	get_line(char *buff, char *tmp, char **line)
{
	buff[1] = 0;
	if (buff[0] != '\n')
	{
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		free (tmp);
	}
}

void	get_next_line(char **line, int *i, t_var *var)
{
	char	buff[2];
	int		ret;
	char	*tmp;

	tmp = NULL;
	boucle_get_next_line(line, i);
	*i = 0;
	ret = 1;
	buff[0] = 0;
	write(STDOUT_FILENO, "> ", 2);
	while (ret > 0 && buff[0] != '\n')
	{
		ret = read(STDIN_FILENO, buff, 1);
		get_line(buff, tmp, line);
		if (buff[0] == 0)
		{
			var->here_doc_ctrl_d = 1;
			(*i)--;
			break ;
		}
		(*i)++;
	}
	(*i)--;
}

int	here_doc(t_input *input, char *delimiter, t_var *var)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	init_variable_here_doc(var, input);
	line = ft_strdup("");
	while (ft_strcmp(&line[ft_strlen(line) - i], delimiter) == 0)
	{
		get_next_line(&line, &i, var);
		if (var->here_doc_ctrl_d == 1)
		{
			here_doc_ctrl_d_equal_one(var, input, line, delimiter);
			return (0);
		}
	}
	tmp = line;
	line = ft_strjoin(line, "\n");
	free(tmp);
	line = delete_last_line(line);
	if (input->heredoc)
		free(input->heredoc);
	input->heredoc = trim_heredoc(line, get_heredoc_len(line, var), var);
	free (delimiter);
	return (0);
}
