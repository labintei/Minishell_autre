/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:29:51 by labintei          #+#    #+#             */
/*   Updated: 2021/09/27 21:04:39 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_tab(char ***s)
{
	int		i;

	i = -1;
	while ((*s) && (*s)[(++i)])
		free((*s)[i]);
	if ((*s))
		free((*s));
}

void	clear_list_env(t_list_env	**env)
{
	t_list_env	*temp;

	list_start_env(env);
	while ((*env))
	{
		temp = (*env)->next;
		if ((*env)->var)
			free((*env)->var);
		if ((*env)->val)
			free((*env)->val);
		free((*env));
		(*env) = temp;
	}
}

void	clear_t_list_file(t_list_file	**file)
{
	t_list_file		*temp;

	restart_t_list_file(file);
	while ((*file))
	{
		temp = (*file)->next;
		if ((*file)->path)
			free((*file)->path);
		if ((*file)->ambigous)
			free((*file)->ambigous);
		free (*file);
		(*file) = temp;
	}
}

void	clear_cmds(t_list **cmds)
{
	t_list	*temp;

	list_cmds_restart(cmds);
	while ((*cmds))
	{
		temp = (*cmds)->next;
		if ((*cmds)->cmds)
			clear_tab(&((*cmds)->cmds));
		if ((*cmds)->file)
			clear_t_list_file(&((*cmds)->file));
		free(*cmds);
		(*cmds) = temp;
	}
}

void	clear_env(t_env *env)
{
	clear_list_env(&(env->env));
	clear_cmds(&(env->cmds));
	clear_tab(&(env->split_path));
	if (env->line)
		free(env->line);
}
