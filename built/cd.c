/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:01:00 by labintei          #+#    #+#             */
/*   Updated: 2021/09/09 19:49:08 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Retours a verifier */

/* Returns the value of the corresponding key env */
char	*find_value(t_list_env *env, char *key)
{
	t_list_env	*elem;

	elem = env;
	while (elem)
	{
		if (ft_strcmp_cd(key, elem->var) == 0)
		{
			return (elem->val);
		}
		elem = elem->next;
	}
	return (NULL);
}

/* Prints current cd errors */
void	cd_errors(char *path, int err, bool fork)
{
	if (!fork)
		return ;
	if (err == ENOTDIR)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else if (err == ENOENT)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

/* Finds the target path for cd depending on the arguments */
/* revoir la valeur de fork */
char	*find_path_1(t_list *cmds, t_list_env *env, bool fork)
{
	int		length;
	char	*path;

	length = cmds_length(cmds);
	fork = 1;
	if (length < 2)
	{
		path = find_value(env, "HOME");
		if (!path && fork)
			ft_putstr_fd("cd : HOME not set\n", 2);
	}
	else
	{	
		if (cmds->cmds[1][0] == '-' && cmds->cmds[1][1] == '\0')
		{
			path = find_value(env, "OLDPWD");
			if (!path && fork)
				ft_putstr_fd("cd : OLDPWD not set\n", 2);
			else if (fork)
				printf("%s\n", path);
		}
		else
			path = cmds->cmds[1];
	}
	return (path);
}

/* executes the cd commands */
int	cd(t_list *cmds, t_list_env *env, bool fork)
{
	int		ret;
	char	*previous;
	char	*current;

	current = find_path_1(cmds, env, fork);
	if (current == NULL)
		return (CD_ERROR);
	previous = getcwd(NULL, 0);
	ret = chdir(current);
	if (ret)
		cd_errors(current, errno, fork);
	else
	{
		if (previous)
			env_manager("OLDPWD", previous, env);
		current = getcwd(NULL, 0);
		if (current == NULL)
			return (CD_ERROR);
		env_manager("PWD", current, env);
		free(current);
	}
	free(previous);
	return (ret);
}
