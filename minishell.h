/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:16 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/24 16:15:13 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* **************************************** */
/*                INCLUDES                  */
/* **************************************** */

# include "libft/libft.h"
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/dir.h>
# include <readline/readline.h>
# include <readline/history.h>

/* **************************************** */
/*              DEFINITIONS                 */
/* **************************************** */

# define M "Minishell"
# define MAX_MATCHES 1024

/* **************************************** */
/*                 ENUMS                    */
/* **************************************** */

typedef enum error
{
	SYNTAX = 512,
	DIRECT,
	REDIR,
	CMD_NOT_FOUND,
}			t_error;

typedef enum type
{
	OR,
	AND,
	SUBSHELL,
	PIPE,
	CMD,
	READ,
	HEREDOC,
	TRUNC,
	APPEND
}			t_type;

/* **************************************** */
/*             STRUCTURES                   */
/* **************************************** */

typedef struct s_pipe
{
	int		*fdo;
	int		*fdi;
	pid_t	pid1;
	pid_t	pid2;
	char	*path1;
	char	*path2;
	char	**args;
	int		pipefd[2];
}			t_pip;

	typedef struct s_redir
	{
		t_type	mode;
		int		fd;
		int		flag;
		int		q;
		char	*target;
		char	*delim;
	}			t_redir;

typedef struct s_sig
{
	int		flag;
	int		exit_status;
}			t_sig;

typedef struct s_check
{
	int		dquot;
	int		squot;
	int		lpar;
	int		fpar;
	int		par;
	int		special;
}			t_check;

// Main shell structure
typedef struct s_shell
{
	int			exit;
	char		**envp;
	char		*cmd;
	char		*cmd_not_found;
	char		*pwd;
	t_list		*heredoc;
	t_list		*env;
	t_list		*args;
	t_list		*tmp;
	t_list		*redir;
	t_check		check;
	t_list		*ast;
}				t_shell;

typedef int (t_fct)(int ac, char **av, t_shell *vars);

extern t_sig	*g_var;

/* **************************************** */
/*           FUNCTION PROTOTYPES            */
/* **************************************** */

/*---------------------------- PARSING ----------------------------*/

/* Building */
t_list	*ast_builder(t_list **cursor);
int		fill_args(t_shell *vars);
t_list	*create_node(void *content);
char	*tokenizer(char *str, char const *delim);
void	ft_nullenv(t_shell *vars);
void	ft_shlvl(t_shell *vars);

/* Validation */
int		all_checks(t_shell *vars);
int		isvalid_par(t_shell *vars);
int		isvalid_red(t_shell *vars);
int		isvalid_op(t_shell *vars);
int		is_op(char *str);
int		is_par(char *str);
int		isvalid_quotes(t_shell *vars);
int		is_there_red(char *str);
int		is_word(char *str);
int		nodejoin(t_shell *vars);

/* Processing */
int		ft_nodejoin(t_shell *vars);
char	*removequotes(char *str, t_list *s);
char	*old_removequotes(char *str);
t_list	*remove_quotes_from_list(t_list *lst);
char	**_ft_split(char const *s, char b);
void	pop_spaces(t_shell *vars);
void	throw_error(int error, char *file, int *status);
void	process_heredocs(t_shell *vars);

/* Expansion */
char	**split_list(t_list *lst, char sep);
void	expand(t_shell *vars, char **str, char ***arr);
char	**wildcard(char *pattern);
int		append(t_list **s, char c, int type);
char	*expand_wildcard(char **str, t_list **s);
t_list	*ft_str_to_lst(char *str, int flag);
int		get_var_len(char *str);
int		extract_var_value(t_shell *vars, t_list **s, char *str, int q);
t_list	*breakdown(t_shell *vars, char *str);

/*---------------------------- BUILTINS ----------------------------*/

int		cd(int ac, char **av, t_shell *vars);
int		echo(int ac, char **av, t_shell *vars);
int		env(int ac, char **av, t_shell *vars);
int		ft_exit(int ac, char **av, t_shell *vars);
int		pwd(int ac, char **av, t_shell *vars);
int		unset(int ac, char **av, t_shell *vars);
int		export(int ac, char **av, t_shell *vars);
char	*get_env(char *k, t_shell *vars);
char	*ft_strjoin_f(char *s1, char *s2, int free_s);
void	ft_printexport(t_shell	*vars);
void	append_value(char *v, char *av, t_shell *vars);
int		check_builts(char **arr, t_shell *vars, int i);

/*---------------------------- execution ----------------------------*/

int		pipex(t_shell *vars, t_list **node);
int		execution(t_shell *vars, t_list **ast);
char	*get_path(char *cmd, t_shell *vars);
int		exit_execve(char *cmd, t_shell *vars, t_list **ast);
void	skip(t_list **node, int op);
int		traverse_sub(t_shell *vars, t_list **node);
int		execute_cmd(t_shell *vars, t_list **ast);
int		check_builts(char **arr, t_shell *vars, int i);
void	extract_redirections(t_shell *vars, char **original);
int		apply_redirections(t_shell *vars);

#endif
