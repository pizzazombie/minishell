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

#include <stdio.h>
#include "shell.h"

void	ft_del(char **arr, char *str)
{
	int i;

	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	free(str);
}
void	ft_init_shell(t_shell *shell)
{
	shell = (t_shell *)malloc(sizeof(t_shell));
	shell->location = NULL;
}

void	ft_display_path(t_shell *shell)
{
	char *str;
	char buf[4001];
	char *p;

	str = getcwd(buf, 4000);
	ft_printf("\033[34;1;1m%s\033[0m", str);
	ft_putstr(">");
	shell->location = str;
	//free(str);
}
void	ft_cd(char *str)
{
	ft_putchar('\n');
}
void	ft_echo(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
	{
		i++;
	}
	ft_putstr(str + i);
	ft_putchar('\n');
}
void	ft_env(char **env, char *str)
{
	char **args;

	
	if (str[3] == '\0' || str[3] == ';')
		ft_print_env(env);
	else
	{
		args = ft_strsplit(str, ' ');
		if (args[1])
		{
			if (args[2])
			{
				ft_putendl("setenv: Too many arguments.");
				//return (1);
			}
		}
	}
	
}
int	ft_run_commands(char **commands, t_shell *shell, char **env)
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
		else if (ft_strncmp(commands[i], "env", 3) == 0)
			ft_env(env, commands[i]);
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
void	ft_print_env(char **env)
{
	int i;

	i = 0;
	while (env[i] != 0)
	{
		ft_putendl(env[i]);
		i++;
	}
}
char **ft_init_env(char **environ)
{
	char **env;
	int i;

	i = 0;
	env = (char **)malloc(sizeof(char*) * 28);
	while (environ[i] != 0)
	{
		if ((env[i] = ft_strdup(environ[i])) == NULL)
			return (NULL);
		i++;
	}
	env[i] = 0;
	return (env);
}
int main(int ac, char **av, char **environ)
{
	char *str;
	char **commands;
	char **env;

	t_shell shell;

	ft_init_shell(&shell);
	if ( (env = ft_init_env(environ)) == NULL)
		return (1);
	str = ft_strnew(100);
	while (1)
	{
		ft_display_path(&shell);
		get_next_line(0, &str);
		commands = ft_strsplit(str, ';');
		if (ft_run_commands(commands, &shell, env) == 1)
		{
			ft_del(commands, str);
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
