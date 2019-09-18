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
		else if (ft_strncmp(commands[i], "unsetenv ", 8) == 0)
			ft_unsetenv(shell, commands[i]);
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
int	ft_check_name_length(char *str)
{
	int i;
	
	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	return (i);
}
char *ft_parse_input(t_shell *shell, char *str)
{
	int i;
	int j;
	int ii;
	int index;
	char *temp;
	char *temp2;
	char *name;

	i = 0;
	ii = 0;
	//temp2 = ft_strnew(1);
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0')
		{
			ii = i;
			i++;
			j = 0;
			name = ft_strnew(ft_check_name_length(str + i));
			while (str[i] != ' ' && str[i] != '\0')
			{
				name[j] = str[i];
				j++;
				i++;
			}
			if ((index = ft_find_env_var(shell->env, name)) == -1)
			{
				str[ii] = '\0';

				temp = ft_strdup(str);
				ii++;
				while (str[ii] != ' ' && str[ii] != '\0')
					ii++;
				temp2 = ft_strjoin(temp, str + ii);
				free(str);
				str = temp2;
				free(temp);
				i = 0;
				free(name);
				continue ;
			}
			else
			{
				str[ii] = '\0';

				temp = ft_strdup(str);
				ii++;
				while (str[ii] != ' ' && str[ii] != '\0')
					ii++;
				temp2 = ft_strjoin(temp, ft_strchr(shell->env[index], '=') + 1);
				free(temp);
				temp = ft_strjoin(temp2, str + ii);
				free(temp2);
				str = temp;
				i = 0;
				free(name);
				continue ;
			}
		}
		else
		{
			i++;
		}
		
	}
	return (str);
}
int main(int ac, char **av, char **environ)
{
	char *str;
	char **commands;
	//char **env;

	t_shell shell;

	ft_init_shell(&shell);
	if ( (shell.env = ft_init_env(environ, &shell)) == NULL)
		return (1);
	str = ft_strnew(100);
	while (1)
	{
		ft_display_path(&shell);
		get_next_line(0, &str);
		str = ft_parse_input(&shell, str);
//		ft_printf("%s\n", str);
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
