/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:50:07 by labintei          #+#    #+#             */
/*   Updated: 2021/08/31 15:58:52 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MINISHELL_H
#define		MINISHELL_H

#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<readline/readline.h>
#include	<readline/history.h>
#include	<errno.h>
#include	<sys/wait.h>
#include	<sys/time.h>
#include	<sys/stat.h>
#include	<curses.h>
#include	<signal.h>
#include	<fcntl.h>

typedef	struct		s_list_env
{
	char	*var;
	char	*val;
	struct	s_list_env	*next;
	struct	s_list_env	*previous;
}					t_list_env;

typedef	struct		s_list
{
	char	**cmds;
	pid_t	pid;
	char	*cmds_type;
	char	*fd;
	char	type;
	int		pipe[2];
	struct	s_list		*previous;
	struct	s_list		*next;
}					t_list;

typedef	struct		s_env
{
	t_list			*cmds;
	t_list_env		*env;
	char			**split_path;
}					t_env;

//	clear

void		clear_cmds(t_list **cmds);
void		clear_tab(char ***s);
void		clear_env(t_env *env);
void		clear_list_env(t_list_env **env);
void		free_mem(t_env *env);
// OTHER

void		list_cmds_restart(t_list	**cmds);


void		find_exec_path(char **path, t_env *env);

// BUILT_IN

int		cd(t_list *cmds, t_env *env);
int		echo_build(t_list *cmds);
int		unset(t_list *cmds, t_env *env);
int		export_build(t_list *cmds, t_env *env);
int		pwd(void);
int		exit_build(t_env *env);

// PARSING

// COUNT WORD
void		skip_space(char *line, int *j);
int			is_quotes(char c, char *line, int i);
int			count_word(char *line, int *i);
// COUNT char
int			count_char(char *line, int i, t_env *env);
// VIEW-CMDS
void		view_cmds(t_list	**cmds);

// 
int			find_var_and_strlen(char *line, int *j, t_env *env);

// CONVERT ENV


void		get_splitted_path(t_env *env);

void		ft_dup_env(t_list_env **env, char *var, char **val);

void		ft_convert_env(t_list_env **env, char ***stock);
void		view_tab(char **tab);
int			ft_strlen_env(t_list_env	**list, char *var);
void		view_list_env(t_list_env	**l);
void		list_start_env(t_list_env **list);

// ENV

void		stock_env(t_env *env, char **envp);
int			ft_len_env(t_list_env **env);

// CMDS

void		add_cmds(t_list	**cmds);

// UTILS

void		ft_strcpy(char **s, char *copy);

int			ft_strcmp(char *s, char *sbis);
int			ft_second(char c, char	*s, int i);
int			is_alphanum(char c);
char		ft_find(char c, char *s);
int			ft_strlen(char *s);
int			ft_strlen_char(char *s, char c);
char		*ft_strdup(char *copy);
char		*ft_strdup_char(char *copy, char c);
char		*ft_strdup_char_after(char *copy, char c);

// exec

void		exec_cmds(t_env *env);

#endif
