/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:12:24 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/29 20:34:36 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars;

int	path_index(char **envp, char *s)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(s, envp[i], 5))
			return (i);
		i++;
	}
	// need to review and remove and use get_env...
	return (0);
}

int	check_built_ins(char **arr, t_shell *vars)
{
	if (!arr)
		return (FALSE);
	if (!ft_strcmp("pwd", *arr))
		return (pwd(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("cd", *arr))
		return (cd(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("echo", *arr))
		return (echo(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("env", *arr))
		return (env(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("exit", *arr))
		return (ft_exit(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("export", *arr))
		return (export(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("unset", *arr))
		return (unset(ft_arrlen(arr), arr, vars), TRUE);
	return (FALSE);
}

int is_dir(const char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (0);
	return (S_ISDIR(sb.st_mode));
	// handle directory exit status and error
}

char	*get_path(char **envp, char *cmd)
{
	char	**paths;
	char	*checker;
	char	*path;
	int		i;

	if (access(cmd, X_OK) == 0 && is_dir(cmd) != 1)
		return (ft_strdup(cmd));
	paths = ft_split(envp[path_index(envp, "PATH=")] + 5, ':');
	i = 0;
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		checker = ft_strjoin(path, cmd);
		if (!access(checker, X_OK) && !is_dir(checker))
		{
			if 	
			if (!ft_strnstr(checker, "//", ft_strlen(checker)))
				return (ft_free("21", paths, path), checker);
		}
		ft_free("11", checker, path);
	}
	ft_free("2", paths);
	g_vars.cmd_not_found = cmd;
	g_vars.exit = 0;
	return (throw_error(CMD_NOT_FOUND), NULL);
}

void	execution(t_shell *vars)
{
	char	*cmd_path;

	vars->tmp = vars->args;
	while (vars->tmp)
	{
		if (check_built_ins(vars->tmp->arr, vars) == TRUE)
		{
			vars->tmp = vars->tmp->next;
			continue ;
		}
		cmd_path = get_path(vars->envp, *vars->tmp->arr);
		if (!cmd_path)
		{
			vars->tmp = vars->tmp->next;
			continue ;
		}
		pid_t (pid) = fork();
		if (pid == 0)
		{
			if (execve(cmd_path, vars->tmp->arr, vars->envp) == -1)
				perror("execve");
		}
		else
			wait(NULL);
		free(cmd_path);
		vars->tmp = vars->tmp->next;
	}
}
