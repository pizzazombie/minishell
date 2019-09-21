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

void	ft_echo_helper(char **args, char *str, int index)
{
	if (index == 0)
		ft_putchar('\n');
	ft_free_mas(args);
	free(str);
}

void	ft_echo(char *str1)
{
	int		i;
	int		j;
	char	*str;
	char	**args;
	int		index;

	i = 0;
	index = 0;
	ft_putstr(str1);
	str = ft_brakets(ft_strdup(str1));
	args = ft_strsplit_wide(str, ' ');
	if (ft_strncmp(args[0], "-n", 2) == 0 && args[0][2] == '\0')
	{
		i++;
		index++;
	}
	while (args[i] != 0)
	{
		j = 0;
		while (args[i][j] == ' ')
			j++;
		ft_printf("%s ", args[i] + j);
		i++;
	}
	ft_echo_helper(args, str, index);
}
