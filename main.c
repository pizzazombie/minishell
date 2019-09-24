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

void	ft_display_path(t_shell *shell)
{
	char *str;
	char buf[4001];
	char *p;

	str = getcwd(buf, 4000);
	ft_printf("\033[34;1;1m%s\033[0m", str);
	ft_putstr(g_prompt);
}

void	ft_signal(int signal)
{
	char *str;
	char buf[4001];

	if (signal == SIGINT)
	{
		ft_putchar('\n');
		str = getcwd(buf, 4000);
		ft_printf("\033[34;1;1m%s\033[0m", str);
		ft_putstr("(つಠ ʖ̯ ಠ)つ");
	}
}

char	*ft_tilde(char *str, t_shell *shell)
{
	int		i;
	int		ii;
	char	*temp;
	char	*before;
	char	*temp2;

	i = 0;
	while (str[i] != '\0')
		if (str[i] == '~')
		{
			temp = ft_strdup(str + i + 1);
			str[i] = '\0';
			before = ft_strdup(str);
			temp2 = ft_strjoin(before, shell->home);
			free(before);
			before = ft_strjoin(temp2, temp);
			free(temp2);
			free(temp);
			free(str);
			str = before;
			continue ;
		}
		else
			i++;
	return (str);
}

char	*ft_get_input(char *str, t_shell *shell)
{
	ft_display_path(shell);
	signal(SIGINT, ft_signal);
	get_next_line(0, &str);
	if (ft_is_qoute(str) < 0)
		while (ft_is_qoute(str) < 0)
			str = ft_qoute(str);
	if (ft_strncmp(str, "echo ", 5) != 0)
		str = ft_brakets(str);
	str = ft_parse_input(shell, str);
	str = ft_tilde(str, shell);
	return (str);
}

int		main(int ac, char **av, char **environ)
{
	char	*str1;
	char	*str;
	char	**commands;
	t_shell	shell;

	ft_init_shell(&shell);
	if ((shell.env = ft_init_env(environ, &shell)) == NULL)
		return (1);
	while (1)
	{
		str = ft_get_input(str, &shell);
		commands = ft_strsplit_wide(str, ';');
		if (ft_run_commands(commands, &shell) == 1)
		{
			ft_del(commands, str, &shell);
			return (0);
		}
		else
		{
			ft_free_mas(commands);
			free(str);
			continue ;
		}
	}
	return (0);
}
