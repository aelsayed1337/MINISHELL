/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removequotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:58:10 by ahakki            #+#    #+#             */
/*   Updated: 2025/04/26 22:35:39 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*removequotes(char *str)
{
	char	*result;

	int (i), (j), (c);
	if (!str || !(*str))
		return (NULL);
	if (ft_count_char(str, '\'') == 0 && ft_count_char(str, '"') == 0)
		return (str);
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return (free(str), NULL);
	ft_init(3, &i, &j, &c);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && c == 0)
			c = str[i++];
		else if (str[i] == c)
		{
			c = 0;
			i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (free(str), result);
}

void	removequotes_arr(char **arr)
{
	int		i;
	int		len;

	if (!arr)
		return ;
	len = ft_arrlen(arr);
	i = 0;
	while (i < len && arr[i])
	{
		arr[i] = removequotes(arr[i]);
		i++;
	}
}
