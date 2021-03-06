/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:23:47 by rcollas           #+#    #+#             */
/*   Updated: 2021/12/06 10:32:23 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAIL 0

# include "parsing.h"
# include "builtin.h"
# include "multipipes.h"
# include "struct.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>

int		ft_echo(t_var *var);
int		ft_env(t_var *var);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_pwd(t_var *var);
int		ft_exit(t_var *var);
int		count_pipes(t_var *var);
int		ft_multipipes(t_var *var, t_builtin *builtin);
int		ft_execve(t_var *var, t_builtin *builtin);
void	free_envar(t_envar *envar);
void	free_all(t_var *var);

#endif
