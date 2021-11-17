/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:48:22 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/07 11:50:39 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	handle_exit_status(int status)
{
	if (WIFEXITED(status))
	{
		EXIT_STATUS = WEXITSTATUS(status);
		if (EXIT_STATUS == 1234567890)
			EXIT_STATUS = 130;
	}
}

int	ft_exec(t_var *var, t_pvar *pvar, int pipe_fd[2])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (ft_dup(var, pipe_fd) == 1)
		{
			EXIT_STATUS = 1;
			return (EXIT_STATUS);
		}
		close_fd(var);
		if (execve(pvar->cmd, var->input->args, NULL) == -1)
		{
			write(2, var->input->args[0],
				  ft_strlen(var->input->args[0]));
			EXIT_STATUS = 127;
			return (EXIT_STATUS);
		}
	}
	waitpid(0, &status, WUNTRACED);
	handle_exit_status(status);
	close_fd(var);
	free_split(pvar->path);
	return (1);
}

int	handle_builtin(t_var *var, int pipe_fd[2], t_builtin *builtin, int ret)
{
	int		saved_stdout;
	int		saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (ft_dup(var, pipe_fd) == 1)
		return (1);
	builtin[ret].func(var);
	close_fd(var);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	return (0);
}

int	ft_execve(t_var *var, t_builtin *builtin)
{
	t_pvar	pvar[1];
	int		ret;
	int		pipe_fd[2];

	ret = is_builtin(var->cmd, builtin);
	if (ret >= 0)
	{
		if (handle_builtin(var, pipe_fd, builtin, ret) == 1)
			return (EXIT_STATUS = 1);
		else
			return (EXIT_STATUS = 0);
	}
	if (ret == -1)
		EXIT_STATUS = 1234567890;
	pvar->path = get_binaries_path(var);
	add_slash(pvar);
	if (get_cmds(pvar, var) == 0)
		return (-1);
	if (ret < 0)
		ft_exec(var, pvar, pipe_fd);
	return (EXIT_STATUS);
}
