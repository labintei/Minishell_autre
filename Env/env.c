/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 17:39:08 by labintei          #+#    #+#             */
/*   Updated: 2021/09/23 14:31:25 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_env	*sub_add_arg_2(char *key, char *value)
{
	t_list_env	*next;

	next = (t_list_env *)malloc(sizeof(t_list_env));
	if (!next)
	{
		ft_putstr_fd("Failure to allocate memory\n", 2);
		exit (EXIT_FAILURE);
	}
	next->var = ft_strdup(key);
	next->val = ft_strdup(value);
	next->next = NULL;
	if (!next->var || ! next->val)
	{
		ft_putstr_fd("Failure to allocate memory\n", 2);
		exit (EXIT_FAILURE);
	}
	return (next);
}

int	add_arg_2(t_list_env *env, char *key, char *value)
{
	t_list_env	*next;
	t_list_env	*current;

	current = env;
	if (ft_strcmp_cd(env->var, "") == 0 && ft_strcmp(env->val, "") == 0)
	{
		free(env->var);
		free(env->val);
		env->var = ft_strdup(key);
		env->val = ft_strdup(value);
		if (!env->var || !env->val)
		{
			ft_putstr_fd("Failure to allocate memory\n", 2);
			exit (EXIT_FAILURE);
		}
		return (0);
	}
	next = sub_add_arg_2(key, value);
	if (!next)
	{
		ft_putstr_fd("Failure to allocate memory\n", 2);
		exit (EXIT_FAILURE);
	}
	while (current->next)
		current = current->next;
	current->next = next;
	return (0);
}

int	env_manager(char *key, char *value, t_list_env *env)
{
	t_list_env	*elem;

	elem = env;
	while (elem)
	{
		if (ft_strcmp_cd(elem->var, key) == 0)
		{
			if (!value)
				return (0);
			free(elem->val);
			elem->val = ft_strdup(value);
			if (!elem->val && value)
			{
				ft_putstr_fd("Failure to allocate memory\n", 2);
				exit (EXIT_FAILURE);
			}
			return (0);
		}
		elem = elem->next;
	}
	if ((add_arg_2(env, key, value)) != 0)
		return (-1);
	return (0);
}

void		list_start_env(t_list_env **list)
{
	while ((*list) && ((*list)->previous))
	{
		*list = (*list)->previous;
	}
}

int			ft_len_env(t_list_env **env)
{
	int		i;
	t_list_env	*c;

	i = 0;
	list_start_env(env);
	c = (*env);
	while(c)
	{
		i++;
		c = c->next;
	}
	return(i);
}

int			view_list_env(t_list_env	**l)
{
	t_list_env		*c;

	list_start_env(l);
	c = (*l);
	printf("\n");
	while(c)
	{
		printf("%s=", c->var);
		printf("%s\n", c->val);
		c = c->next;
	}
	printf("\n");
	return(0);
}

int			add_arg(t_list_env	*list, char *var, char *val)
{
	ft_strcpy(&(list->var), var);
//	if(var != NULL && list->var == NULL)
//		return(0);
	ft_strcpy(&(list->val), val);
//	if(val != NULL && list->val == NULL)
//		return(0);
	return(1);
}


int			add_list_env(t_list_env	**list, char	*var, char *val, int i)
{
	t_list_env	*new;

	new = malloc(sizeof(t_list_env));
//	if(!new)
//		return(0);
	new->previous = NULL;
	new->next = NULL;
	new->var = NULL;
	new->val = NULL;
	if(i != 0)
	{
		(*list)->next = new;
		new->previous = *list;
	}
	(*list) = new;
	if(!(add_arg(new, var, val)))
		return(0);
	return(1);
}

void		stock_env(t_env		*env, char **envp)
{
	int		i;
	char	*var;
	char	*val;

	i = 0;
	var = NULL;
	val = NULL;
	while(envp && envp[i])
	{
		var = ft_strdup_char(envp[i], '=');
		val = ft_strdup_char_after(envp[i], '=');
		if(var && ma_strcmp(var, "_") != 0)
		{
			/*if(!(*/add_list_env(&(env->env), var , val, i);/*))*/
			//	exit_fatal(1, env);
		}
		if(var)
			free(var);
		if(val)
			free(val);
		i++;
	}
}

int			ft_strlen_env(t_list_env **list, char *var)
{
	t_list_env	*l;

	list_start_env(list);
	l = (*list);
	while(l)
	{
		if(l->var && ft_strcmp(l->var, var))
			return(ft_strlen(l->val));
		l = l->next;
	}
	return(0);
}
