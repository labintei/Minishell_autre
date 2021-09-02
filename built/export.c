/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:39:11 by labintei          #+#    #+#             */
/*   Updated: 2021/09/02 21:04:53 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// PREMIER ELEMENT A LA PLUS PEITE VALEUR
// SWAP LIST si un element [lus grand que son precedent
void		swap_list(t_list_env	**env, t_list_env **i)
{
	t_list_env	*next;
	t_list_env	*previous;

	next = (*env)->next;
	previous = (*env)->previous;
	(*env)->next = (*i)->next;
	(*env)->previous = (*i)->previous;
	(*i)->next = next;
	(*i)->previous = previous;
}

int			sort_str(char *s, char *sbis)
{
	int		i;

	i = 0;
	if(!sbis || !s)
		return(0);
	while(s && sbis && s[i] && sbis[i] && s[i] == sbis[i])
		i++;
	return(s[i] - sbis[i]);
}

void		list_sort(t_list_env	**env)
{
	t_list_env	*temp;
	int		g;

	g = 0;
	list_start_env(env);
	while(g == 0)
	{
		if((*env) && (*env)->next)
		{
			temp = (*env)->next;
			while((*env) && (*env)->next && (*env)->var && sort_str((*env)->var, (*env)->next->var) > 0)
				swap_list(&(*env), &((*env)->next));
			(*env) = temp;
		}
		else
			g = 1;
	}
}

void		env_sans_arg(t_list_env		**env)
{
	list_sort(env);
//	view_list_env(*env);
}

void		list_env_end(t_list_env		**env)
{
	list_start_env(env);
//	printf("\n0\n");
	while((*env) && (*env)->next)
		(*env) = (*env)->next;
//	printf("\n1\n");
}

int			ft_find_env(t_list_env **env, char *var)
{
	int			g;

	g = 0;
	list_start_env(env);
	while((*env) && g == 0)
	{
//		if((*env)->var && (*env)->val)
//			printf("\n VAR : %s VAL : %s\n", (*env)->var, (*env)->val);
		if((*env) && (*env)->var && ft_strcmp((*env)->var, var))
			return(1);
		if((*env) && (*env)->next)
			(*env) = (*env)->next;
		else
			g = 1;
	}
	return(0);
}

void		change_value(t_list_env **env, char *var, char *val)
{
	if((*env))
	{
		if((*env) && (*env)->var && ft_strcmp((*env)->var, var))
		{
			if((*env)->val)
				free((*env)->val);
			ft_strcpy(&((*env)->val), val);
		}
	}
}

int			export_build(t_list *cmds, t_env *env)
{
	int		i;
	char	*var;
	char	*val;
	char	*temp;
	char	*to;
	int		g;

	g = 4;
	i = 1;
//	printf("AAAAAAAAAAAAAAAAAAAAA");
	while(cmds->cmds && cmds->cmds[0] && cmds->cmds[i])
	{
		if(ft_find('=',cmds->cmds[i]))
		{
			var = ft_strdup_char(cmds->cmds[i], '=');
			val = ft_strdup_char_after(cmds->cmds[i], '=');
			ft_strcpy(&temp, var);
			ft_strcpy(&to, val);
//			printf("\nVAR : %s\n", var);
//			printf("\nVAL : %s\n", val);
			if(var && ft_find_env(&(env->env), var))
			{
				change_value(&(env->env), var, val);
			}	
			else
			{
//				write(1, "A", 1);
//				printf("\ENTRE1\n");
//				list_env_end(&(env->env));
				//printf("\n2\n");
//				if((env->env)->var)
//				printf("\nLast elem %s\n", (env->env)->var);
				add_list_env(&(env->env), temp, to, g);
			}
			if(var)
				free(var);
			if(val)
				free(val);
			if(temp)
				free(temp);
			if(to)
				free(to);
		}
		i++;
	}
	if(cmds->cmds[0] && !cmds->cmds[1])
	{
		env_sans_arg(&(env->env));
	}
	return(0);
}

/* a revoir Lauranne/Mahaut 
int			export_build(t_list *a, t_env *env)
{
    (void)a;
    (void)env;
	int		i;
	char	*val;
	char	*env_stock;

	i = 1;
	if(a->s && a->s[0] && a->s[1])
	{
		while(a->s[i])
		{
			if(a->s[i] && ft_find('=',a->s[i]))
			{
				val = NULL;
				env_stock = NULL;
				copy_jusqua(&val, a->s[i], '=');
				copy_apres(&env_stock, a->s[i], '=');
				if(val && !ft_find_env(val, env->env_s->first))
					ajout_env(val,env_stock, env->env_s);
				else if(val && ft_find_env(val, env->env_s->first))
					replace_env(val, env_stock, env->env_s); 
			}
			i++;
		}
	}
	return(0);
}
*/
