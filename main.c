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



int	ft_run_commands(char **commands, t_shell *shell)
{
	int i;

	i = 0;
	while (commands[i] != 0)
	{
		if (ft_strncmp(commands[i], "exit", 4) == 0)
		{
			return (1);
		}
		else if (ft_strncmp(commands[i], "echo ", 5) == 0)
			ft_echo(commands[i] + 5);
		else if (ft_strncmp(commands[i], "cd ", 3) == 0)
			ft_cd(commands[i]);
		else if (ft_strncmp(commands[i], "setenv ", 7) == 0)
			ft_setenv(shell, commands[i]);
		else if (ft_strncmp(commands[i], "env", 3) == 0)
			ft_env(shell, commands[i]);
		else if (ft_strncmp(commands[i], "pwd", 3) == 0)
			ft_pwd(commands[i], shell);
		//ft_putchar('\n');
		else
		{
			ft_putstr("minishell: command not found: ");
			ft_putendl(commands[i]);
		}
	//	ft_putchar('\n');
		i++;
	}
	return (0);
}
void	ft_parse_input(char **env, char *str)
{
	int i;

	//if ()
}
int main(int ac, char **av, char **environ)
{
	char *str;
	char **commands;
	//char **env;

	t_shell shell;

	ft_init_shell(&shell);
	if ( (shell.env = ft_init_env(environ)) == NULL)
		return (1);
	str = ft_strnew(100);
	while (1)
	{
		ft_display_path(&shell);
		get_next_line(0, &str);
		commands = ft_strsplit(str, ';');
		if (ft_run_commands(commands, &shell) == 1)
		{
			ft_del(commands, str, shell.env);
			return (0);
		}
		else
		{
			continue ;
		}
		
		
		//ft_get_input()
		
	}
	return (0);
}
