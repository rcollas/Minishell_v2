/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:57:39 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/16 11:57:43 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

int	builtin_first_cmd(t_pvar *pvar, t_var *var, int	**pipefd, int i)
{
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	else
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	close_fd(var);
	(pvar->builtin)[pvar->ret].func(var);
	exit (0);
}

int	builtin_in_between_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	else
		dup2(pipefd[i][0], STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	else
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	close_fd(var);
	(pvar->builtin)[pvar->ret].func(var);
	exit (0);
}

int	builtin_last_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	else
		dup2(pipefd[i][0], STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	close_fd(var);
	(pvar->builtin)[pvar->ret].func(var);
	exit (0);
}

int	proceed_builtin_pipes(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	if (i == 0)
	{
		builtin_first_cmd(pvar, var, pipefd, i);
		return (0);
	}
	else if (i == pvar->cmd_nb - 1)
	{
		builtin_last_cmd(pvar, var, pipefd, i);
		return (0);
	}
	else
	{
		builtin_in_between_cmd(pvar, var, pipefd, i);
		return (0);
	}
}