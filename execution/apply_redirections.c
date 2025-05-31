/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 05:26:59 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/31 02:11:22 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*get_heredoc_node(t_shell *vars)
{
	t_redir	*hd;

	hd = (t_redir *)vars->heredoc->content;
	vars->heredoc = vars->heredoc->next;
	return (hd);
}

int	expand_target(t_shell *vars, char **str)
{
	t_list	*lst;
	char	**arr;
	char	*original;

	original = alloc(0, ft_strdup(*str), 0);
	lst = breakdown(vars, *str);
	*str = alloc(0, ft_lst2str(lst), 0);
	*str = expand_wildcard(str, &lst);
	arr = split_list(lst, ' ');
	if (!arr || (ft_arrlen(arr) != 1 && *arr))
		return (g_var->exit_status = 1, \
		throw_error(REDIR, original, NULL), FALSE);
	*str = *arr;
	return (TRUE);
}

int	open_file(t_redir *r, char **filename)
{
	int	dup;

	r->fd = open(*filename, r->flag, 0644);
	if (r->fd < 0)
		return (printfd(2, M": %s: %s\n", \
			*filename, strerror(errno)), FALSE);
	if (r->mode == READ || r->mode == HEREDOC)
		dup = dup2(r->fd, STDIN);
	else
		dup = dup2(r->fd, STDOUT);
	if (dup == -1)
		return (perror("dup2"), close(r->fd), FALSE);
	if (r->mode == HEREDOC)
		unlink(r->target);
	close(r->fd);
	return (TRUE);
}

void	perform_dups(int save_in, int save_out)
{
	int	i;

	i = dup2(save_in, STDIN_FILENO);
	i = dup2(save_out, STDOUT_FILENO);
	if (save_in != -1)
		close(save_in);
	if (save_out != -1)
		close(save_out);
	if (i <= -1)
		return (perror("dup2"));
}

int	apply_redirections(t_shell *vars)
{
	t_redir	*r;
	t_list	*tmp;
	char	*expanded;
	int		in;
	int		out;

	in = dup(STDIN);
	out = dup(STDOUT);
	if (in == -1 || out == -1)
		return (perror("dup"), -1);
	tmp = vars->redir;
	while (tmp)
	{
		r = (t_redir *)tmp->content;
		expanded = alloc(0, ft_strdup(r->target), 0);
		if (r->mode != HEREDOC && expand_target(vars, &expanded) == FALSE)
			return (perform_dups(in, out), -1);
		if (open_file(r, &expanded) == FALSE)
			return (g_var->exit_status = 1, perform_dups(in, out), -1);
		tmp = tmp->next;
	}
	close(in);
	close(out);
	return (TRUE);
}
