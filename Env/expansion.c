/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 17:39:38 by labintei          #+#    #+#             */
/*   Updated: 2021/09/27 23:10:11 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(char *str, int n)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * n + 1);
	if (!res)
		return (NULL);
	while (str[i] && i < n)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_get_val(char *var, t_env *env)
{
	t_list_env	*tmp;

	tmp = env->env;
	while (tmp && strcmp(tmp->var, var) != 0)
		tmp = tmp->next;
	free(var);
	if (tmp && tmp->val)
		return (tmp->val);
	return (NULL);
}

int	ft_search_var(char *line, t_list_env *tmp, int *i, char *res)
{
	int		j;

	j = (*i) + 1;
	while (is_alphanum(line[j]) > 0)
		j++;
	res = ft_strndup(&line[(*i) + 1], j - (*i) - 1);
	while (tmp && strcmp(tmp->var, res) != 0)
		tmp = tmp->next;
	if (res)
		free(res);
	(*i) = j;
	if (tmp && tmp->val)
		return (ft_strlen(tmp->val));
	else
		return (0);
}

int	ft_count_char(char *line, t_env *env)
{
	int			i;
	int			j;
	int			count;
	char		*res;
	t_list_env	*tmp;

	i = 0;
	j = 0;
	count = 0;
	res = NULL;
	while (line[i])
	{
		tmp = env->env;
		if (line[i] == '$')
			count += ft_search_var(line, tmp, &i, res);
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	ft_expansion_var(char *line, t_env *env, char **tmp, int (*h)[3])
{
	int		j;

	j = (*h)[0] + 1;
	while (is_alphanum(line[j]) > 0)
		j++;
	(*tmp) = ft_strndup(&line[((*h)[0]) + 1], j - (*h)[0] - 1);
	(*h)[0] = j;
	j = 0;
	(*tmp) = ft_get_val((*tmp), env);
	printf("\nTEMP %s\n", (*tmp));
}

int	ft_expansion_bis(char *tmp, char **res, int *j)
{
	int		c;

	c = 0;
	if (tmp)
	{
		while (tmp[c])
		{
			(*res)[(*j)] = tmp[c];
			c++;
			(*j)++;
		}
	}
}

void	init_h(int	(*h)[3])
{
	(*h)[0] = 0;
	(*h)[1] = 0;
	(*h)[2] = 0;
}

char	*ft_expansion(char *line, t_env *env)
{
	int		h[3];
	char	*res;
	char	*tmp;

	init_h(&(h));
	res = malloc(sizeof(char) * (ft_count_char(line, env) + 1));
	if (!res)
		exit_fatal(1, env);
	while (line[(h[0])])
	{
		if (line[h[0]] == '$')
		{
			ft_expansion_var(line, env, &tmp, &h);
			printf("\n%s\n",tmp);
			ft_expansion_bis(tmp, &res, &(h[2]));
		}
		else
		{
			res[(h[2])] = line[(h[0])];
			(h[2])++;
			(h[0])++;
		}
	}
	res[(h[2])] = '\0';
	return (res);
}
