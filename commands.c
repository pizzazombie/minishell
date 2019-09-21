/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkami <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:32:08 by mkami             #+#    #+#             */
/*   Updated: 2019/09/16 18:32:10 by mkami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_change_prompt(t_shell *shell)
{
	shell->prmpt % 10 == 1 ? g_prompt = "⚡" : g_prompt;
	shell->prmpt % 10 == 2 ? g_prompt = "(ノಠ益ಠ)ノ彡┻━┻" : g_prompt;
	shell->prmpt % 10 == 3 ? g_prompt = "╰( ͡° ͜ʖ ͡° )つ──☆*:・ﾟ" : g_prompt;
	shell->prmpt % 10 == 4 ? g_prompt = "༼ つ ▀̿_▀̿ ༽つ" : g_prompt;
	shell->prmpt % 10 == 5 ? g_prompt = "(ง ͡ʘ ͜ʖ ͡ʘ)ง" : g_prompt;
	shell->prmpt % 10 == 6 ? g_prompt = "(⌐■_■)–︻╦╤─" : g_prompt;
	shell->prmpt % 10 == 7 ? g_prompt = "▄︻̷̿┻̿═━一" : g_prompt;
	shell->prmpt % 10 == 8 ? g_prompt = "❤" : g_prompt;
	shell->prmpt % 10 == 9 ? g_prompt = "∞" : g_prompt;
	shell->prmpt % 10 == 0 ? g_prompt = "$>" : g_prompt;
	shell->prmpt++;
}

void	ft_command_not_found(char *str)
{
	char **args;

	args = ft_strsplit_wide(str, ' ');
	if (args[0] == 0)
	{
		ft_free_mas(args);
		return ;
	}
	ft_putstr("minishell: command not found: ");
	ft_putendl(args[0]);
	ft_free_mas(args);
}

int		ft_exit(char *str)
{
	char **args;

	args = ft_strsplit_wide(str, ' ');
	if ((args[0][4] == '\0' || args[0][4] == ' ') && args[1] == 0)
	{
		ft_free_mas(args);
		return (1);
	}
	if (args[0][4] != '\0' && args[0][4] != ' ')
	{
		ft_free_mas(args);
		return (-1);
	}
	else
		ft_putendl("exit: Expression Syntax.");
	ft_free_mas(args);
	return (-1);
}

void	ft_echo_helper(char **args, char *str, int index)
{
	if (index == 0)
		ft_putchar('\n');
	ft_free_mas(args);
	free(str);
}

void	ft_echo(char *str1)
{
	t_var	p;
	char	*str;
	char	**args;
	int		index;

	p.i = 1;
	index = 0;
	str = ft_brakets(ft_strdup(str1));
	args = ft_strsplit_wide(str, ' ');
	if (args[1] == 0)
		ft_putchar('\n');
	else if (ft_strncmp(args[1], "-n", 2) == 0 && args[1][2] == '\0')
	{
		p.i++;
		index++;
	}
	while (args[p.i] != 0)
	{
		p.j = 0;
		while (args[p.i][p.j] == ' ')
			p.j++;
		ft_printf("%s ", args[p.i] + p.j);
		p.i++;
	}
	ft_echo_helper(args, str, index);
}
