/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:03:58 by ahakki            #+#    #+#             */
/*   Updated: 2025/04/16 17:00:30 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_option(char *s)
{
	int	i;

	i = 1;
	if (!s)
		return (FALSE);
	if (s[0] != '-')
		return (FALSE);
	while (s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (TRUE);
	return (FALSE);
}

int	echo(int ac, char **av)
{
	int i;
	int check;

	check = 0;
	i = 1;
	if (ac == 1)
		return (printf("\n"), TRUE);
	while (av[i])
	{
		if (is_option(av[i]) == FALSE)
			break ;
		i++;
	}
	if (i > 1)
		check = 1;
	while (av[i])
		printf("%s", av[i++]);
	if (!check)
		printf("\n");
	return (TRUE);
}

int main(int ac, char **av)
{
	echo(ac, av);
	return (0);
}
