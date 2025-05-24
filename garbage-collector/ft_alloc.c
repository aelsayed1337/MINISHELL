/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:49:07 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/24 19:23:27 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_alloc(size_t size, void *content, char c)
{
	static t_list	*head;
	t_list			*new_node;


	if (content)
	{
		new_node = ft_lstnew(content);
		if (!new_node)
			return (NULL);
		new_node->type = c;
		ft_lst_add_back(&head, new_node);
		return (content);
	}
	else if (c == 'M')
	{
		new_node = ft_lstnew(malloc(size));
		if (!new_node)
			return (NULL);
		new_node->type = c;
		ft_lst_add_back(&head, new_node);
		return (new_node->content);
	}
	else if (c == 'F')
		free_all_memory(&head);
	return (NULL);
}

void	*ft_list2(size_t size)
{
	return (ft_alloc(size, NULL, 'M'));
}

void	ft_exit2(int status)
{
	ft_alloc(0, NULL, 'F');
	exit(status);
}
