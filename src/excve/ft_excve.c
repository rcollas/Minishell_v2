/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:48:22 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/29 17:24:10 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_path(t_var *var, char**path_fromenvp)
{
	char	*path_final;
	char	*path_semi_final;
	int		i;

	i = 0;
	while (path_fromenvp[i])
	{
		path_final = 0;
		path_semi_final = ft_strjoin(path_fromenvp[i], "/");
		path_final = ft_strjoin(path_semi_final, var->input->cmd);
		if (access(path_final, F_OK) == 0)
			return (path_final);
		if (path_final)
			free (path_final);
		i++;
	}
	if (var->input->cmd[0] == '/'
		&& access(&var->input->cmd[0], F_OK) == 0)
		return (&var->list->content[0]);
	return (NULL);
}

int	execve_error(t_var *var)
{
	write (2, "minishell: ", 11);
	write(2, var->input->cmd, ft_strlen(var->input->cmd));
	ft_putendl_fd(": command not found", 2);
	return (-1);
}


int	ft_execve(t_var *var, t_builtin *builtin)
{
	char 	*path_final;
	char	**path_fromenvp;
	pid_t	pid;
	int	ret;
	
	path_final = ft_envar_find_content(var->envar, "PATH");
	path_fromenvp = ft_split(path_final, ':');
	path_final = get_path(var, path_fromenvp);
	ret = is_builtin(var->cmd, builtin);
	if (ret == 6)
		builtin[ret].func(var);
	pid = fork();
	if (pid == 0)
	{
		if (var->IN_FD > 0)
			dup2(var->IN_FD, STDIN_FILENO);
		if (var->OUT_FD > 0)
			dup2(var->OUT_FD, STDOUT_FILENO);
		if (ret >= 0)
			builtin[ret].func(var);
		else if (execve(path_final, var->input->args, NULL) == -1)
		{
			execve_error(var);
			exit (1);
		}
	}
	if (var->IN_FD > 0)
		close(var->IN_FD);
	if (var->OUT_FD > 0)
		close(var->OUT_FD);
	waitpid(0, 0, 0);
	return (0);
}
