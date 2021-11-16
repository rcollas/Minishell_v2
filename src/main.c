/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:23:03 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/05 20:02:56 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	EXIT_STATUS;

int	is_builtin(char *line, t_builtin *builtin)
{
	int	i;

	i = 0;
	while (builtin[i].cmd)
	{
		if (ft_strcmp(line, builtin[i].cmd) == 1)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	exec_minishell(t_var *var, t_builtin *builtin)
{
	var->save_stdin = dup(STDIN_FILENO);
	var->save_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		var->cmd = readline("minishell $> ");
		if (!var->cmd)
			break ;
		add_history(var->cmd);
		if (get_arguments(var) == -1)
		{
			free(var->cmd);
			continue ;
		}
		else if (var->input == NULL)
		{
			free_input(var);
			free(var->cmd);
			continue ;
		}
		else if (var->input->cmd == NULL)
		{
			if (var->input->IN_FD > 0)
			{
				close(var->input->IN_FD);
				dup2(var->save_stdin, STDIN_FILENO);
			}
			if (var->input->OUT_FD > 0)
			{
				close(var->input->OUT_FD);
				dup2(var->save_stdout, STDOUT_FILENO);
			}
			free_input(var);
			free(var->cmd);
			continue ;
		}
		else if (var->cmd_nb > 1)
		{
			EXIT_STATUS = 123456789;
			ft_multipipes(var, builtin);
		}
	    else
		{
			ft_execve(var, builtin);
		}
		dup2(var->save_stdin, STDIN_FILENO);
		dup2(var->save_stdout, STDOUT_FILENO);
		free_input(var);
		free(var->cmd);
	}
    return (0);
}

int	main(int ac, char **av, char **env)
{
	t_builtin	*builtin;
	t_var		var[1];
	t_envar		*envar;
	t_envar		*export;

	builtin = malloc(sizeof(t_builtin) * 8);
	var->cd = (t_cd *)malloc(sizeof(t_cd));
	init_builtin(builtin);
	init_var(var, env, ac);
	(void)av;
	envar = NULL;
	var->cd->exit_cd = 0;
	export = NULL;
	EXIT_STATUS = 0;
	get_env_var(var, &envar);
	get_env_var(var, &export);
	var->envar = envar;
	var->export = export;
	signal(SIGINT, handle_sigusr1);
	signal(SIGQUIT, handle_sigusr1);
	signal(SIGTSTP, handle_sigusr1);
	exec_minishell(var, builtin);
	return (0);
}