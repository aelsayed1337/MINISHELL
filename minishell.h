/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:16 by aelsayed          #+#    #+#             */
/*   Updated: 2025/02/20 18:26:44 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "signal.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum error
{
	SYNTAX,
	CHARS,
	CMD_NOT_FOUND
}			t_error;

typedef struct s_check
{
	int		dquot;
	int		squot;
	int		lpar;
	int		fpar;
	int		par;
	int		special;
}				t_check;

typedef struct s_shell
{
	char		**envp;
	char		*cmd;
	t_list		*args;
	t_list		*tmp;
	t_check		check;
	int			exit;
}				t_shell;

// Parsing Functions
void	fill_args(char *str);

#endif