/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:07:09 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/19 23:46:50 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define FAIL 0
# define SUCCESS 1

# include "../libft/libft.h"
# include "struct.h"
# include "parsing.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

void	add_slash(t_pvar *pvar);
char	**get_binaries_path(t_var *var);
int	exec(t_pvar *pvar, t_var *var, int **pipefd, pid_t *pids);

#endif