/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 17:40:31 by labintei          #+#    #+#             */
/*   Updated: 2021/09/21 14:18:36 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//rajout de env par mahaut 
int			is_build(char *s)
{
	if (s && *s)
	{
		if (ma_strcmp(s, "echo") || ma_strcmp(s, "cd") || ma_strcmp(s, "pwd") \
		|| ma_strcmp(s, "unset") || ma_strcmp(s, "export") \
		|| ma_strcmp(s, "exit") || ma_strcmp(s, "env"))
			return(1);
	}
	return(0);
}

/* Fonction qui va permettre d executer les builtins */
int		exec_build(t_list	*a, t_env *env)
{
	if (a->cmds && !ma_strcmp(a->cmds[0], "cd") /*&& a->is_fork == 0*/)
		return (cd(a, env->env, a->is_fork));
	else if (a->cmds && !ma_strcmp(a->cmds[0], "echo"))
		return (echo_build(a));
	else if (a->cmds && !ma_strcmp(a->cmds[0], "unset"))
		return (unset(a, env));
	else if (a->cmds && !ma_strcmp(a->cmds[0], "export"))
	{
		return (export_build(a, env));
	}
	else if (a->cmds && !ma_strcmp(a->cmds[0], "pwd"))
		return (pwd(env));
	else if (a->cmds && !ma_strcmp(a->cmds[0], "env"))
		return (view_list_env(&(env->env)));//Lauranne: verifier qu il n y a pas d autre option
	else if (a->cmds && !ma_strcmp(a->cmds[0], "exit") && a->is_fork == 0)
		return (exit_build(env, a, a->is_fork));
	return (0);
}