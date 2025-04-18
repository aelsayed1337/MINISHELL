/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:49:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/18 15:17:03 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars;
void	reconfigure(t_shell *vars);
void	split_with_operators(t_shell *vars);

void	throw_error(int error)
{
	if (error == SYNTAX)
		printfd(2, "Invalid Syntax : Something is missing \" or ' or ( or )\n");
	if (error == OP)
		printfd(2, "Invalid Syntax : Error in operators input\n");
	if (error == CMD_NOT_FOUND)
		printfd(2, "Command not found : %s\n", g_vars.cmd_not_found);
	g_vars.exit = 127;
}

int	ft_nodejoin(t_shell *vars)
{
	char *(new_content), *(tmp_content);
	t_list *(to_delete), *(tmp) = vars->args;
	if (tmp && is_op((char *)tmp->content))
		return (throw_error(OP), FALSE);
	while (tmp && tmp->next)
	{
		tmp_content = (char *)tmp->content;
		if (!is_op(tmp_content) && !is_op((char *)tmp->next->content) && \
			!is_par(tmp_content) && !is_par((char *)tmp->next->content))
		{
			new_content = ft_strjoin(tmp_content, (char *)tmp->next->content);
			if (!new_content)
				return (FALSE);
			free(tmp->content);
			tmp->content = new_content;
			to_delete = tmp->next;
			tmp->next = tmp->next->next;
			ft_lstdelone(to_delete, free);
		}
		else
			tmp = tmp->next;
	}
	if (tmp && is_op((char *)tmp->content))
		return (throw_error(OP), FALSE);
	return (TRUE);
}

void	pop_spaces(t_shell *vars)
{
	t_list	*new;
	t_list	*tmp;
	t_list	*next;
	t_list	*node;

	tmp = vars->args;
	new = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (ft_iswhitespace(tmp->content) == FALSE)
		{
			node = ft_lstnew(ft_strdup(tmp->content));
			node->arr = ft_arrdup(tmp->arr);
			ft_lstadd_back(&new, node);
		}
		ft_free("12", tmp->content, tmp->arr);
		free(tmp);
		tmp = next;
	}
	vars->args = new;
}

void	split_cmds_args(t_shell *vars)
{
	int	i;

	vars->tmp = vars->args;
	while (vars->tmp)
	{
		vars->tmp->arr = _ft_split(vars->tmp->content, ' ');
		if (!vars->tmp->arr)
			return ;
		i = 0;
		while (vars->tmp->arr[i])
		{
			vars->tmp->arr[i] = removequotes(vars->tmp->arr[i]);
			i++;
		}
		vars->tmp = vars->tmp->next;
	}
	pop_spaces(vars);
}

int	fill_args(t_shell *vars)
{
	char	*token;

	if (!vars->cmd || !*(vars->cmd) || ft_iswhitespace(vars->cmd))
		return (FALSE);
	token = ft_strtok(vars->cmd, "'\"()|&");
	vars->args = NULL;
	while (token)
	{
		ft_lstadd_back(&vars->args, ft_lstnew(token));
		vars->args->arr = NULL;
		token = ft_strtok(NULL, "'\"()|&");
	}
	if (!ft_check(vars))
		return (FALSE);
	split_cmds_args(vars);
	split_with_operators(vars);
	// reconfigure(vars);
	// ft_lstiter(vars->args, printf);
	printf("----------------------------------\n\n\n");
	return (TRUE);
}

int	is_delim(char *s)
{
	return ((s[0] == '&' && s[1] == '&') || \
		(s[0] == '|' && s[1] == '|'));
}

int	is_closed_here(char c, int *quote, int *depth)
{
	if (*quote)
	{
		if (c == *quote)
			*quote = 0;
	}
	else
	{
		if (c == '\'' || c == '"')
			*quote = c;
		else if (c == '(')
			(*depth)++;
		else if (c == ')' && *depth > 0)
			(*depth)--;
	}
	return (*quote == 0 && *depth == 0);
}

void	split_with_operators(t_shell *vars)
{
	t_list	*new;
	int		i;
	int		start;
	int		depth;
	int		quote;

	ft_init(4, &i, &start, &depth, &quote);
	while (vars->cmd[i])
	{
		is_closed_here(vars->cmd[i], &quote, &depth);
		if (is_delim(&vars->cmd[i]) && !quote && !depth)
		{
			if (i > start)
				ft_lstadd_back(&new, ft_lstnew(ft_strndup(&vars->cmd[start], i - start)));
			ft_lstadd_back(&new, ft_lstnew(ft_strndup(&vars->cmd[i], 2)));
			i += 2;
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		ft_lstadd_back(&new, ft_lstnew(ft_strdup(&vars->cmd[start])));
}
