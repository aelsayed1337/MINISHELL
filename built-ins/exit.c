/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:19:39 by ahakki            #+#    #+#             */
/*   Updated: 2025/06/01 00:44:35 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_atoi(char const *str, int *err)
{
	unsigned int	i;
	int				sign;
	long			n;

	i = 0;
	sign = 1;
	n = 0;
	while (ft_strchr(WHITE, str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] <= '9' && str[i] >= '0')
	{
		if (sign == 1 && (n > (LONG_MAX - (str[i] - '0')) / 10))
			return ((*err = FALSE), -1);
		if (sign == -1 && (n < (LONG_MIN + (str[i] - '0')) / 10))
			return ((*err = FALSE), 0);
		n = n * 10 + (str[i++] - '0');
	}
	if (str[i] && !ft_isdigit(str[i]))
		*err = FALSE;
	return (n * sign);
}

unsigned char	check_args(char *str, int *error)
{
	unsigned char	result;
	char			*trim;

	trim = (char *)alloc(0, ft_strtrim(str, WHITE), 0);
	result = (unsigned char)_atoi(trim, error);
	return (result);
}

int	ft_exit(int ac, char **av, t_shell *vars)
{
	unsigned char	round;
	int				error;

	(void)vars;
	write(1, "exit\n", 5);
	error = TRUE;
	if (ac <= 1)
		clear(0);
	round = check_args(av[1], &error);
	if (error == FALSE)
	{
		g_var->exit_status = 2;
		printfd(2, M": exit: %s: numeric argument required\n", av[1]);
		clear(0);
	}
	if (ac > 2)
	{
		g_var->exit_status = 1;
		return (printfd(2, "exit: too many arguments\n"), 130);
	}
	g_var->exit_status = round;
	return (clear(0), EXIT_SUCCESS);
}
