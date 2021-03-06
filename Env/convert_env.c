/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 17:38:11 by labintei          #+#    #+#             */
/*   Updated: 2021/09/27 22:16:59 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_dup_var_val(t_list_env	*env)
{
	char	*new;
	int		i;
	int		j;

	new = NULL;
	new = malloc(sizeof(char) * \
	(ft_strlen(env->val) + ft_strlen(env->var) + 2));
	i = 0;
	while (env->var && env->var[i])
	{
		new[i] = env->var[i];
		i++;
	}
	new[i] = '=';
	i++;
	j = -1;
	while (env->val && env->val[(++j)])
	{
		new[i] = env->val[j];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_convert_env(t_list_env **env, char ***stock)
{
	int			i;
	t_list_env	*l;

	i = 0;
	list_start_env(env);
	(l) = (*env);
	(*stock) = malloc(sizeof(char *) * (ft_len_env(env) + 1));
	if (!(*stock))
		return (0);
	while ((l))
	{
		(*stock)[i] = ft_dup_var_val((l));
		l = l->next;
		i++;
	}
	(*stock)[i] = NULL;
	return (1);
}

int	ft_len_env(t_list_env **env)
{
	int			i;
	t_list_env	*c;

	i = 0;
	list_start_env(env);
	c = (*env);
	while (c)
	{
		i++;
		c = c->next;
	}
	return (i);
}
