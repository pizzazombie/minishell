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

void	ft_del(char **arr, char *str, char **env)
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
	i = 0;
	while (env[i] != 0)
	{
		free(env[i]);
		i++;
	}
	free(env);
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
void		remove_env_var(int pos, char **env)
{
	free(env[pos]);
	env[pos] = NULL;
	env[pos] = ft_memalloc(2);
}
char	*get_env_var(char **env, char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		tmp = ft_strjoin(var, "=");
		if (ft_strncmp(env[i], tmp, ft_strlen(tmp)))
		{
			free(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
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
				return ;
			}
			ft_print_env(env);
		}
	}
	
}

int	ft_env_index(char **env, char *name)
{
	int i;
	
	i = 0;
	while (env[i] != 0)
	{
		if (strncmp(env[i], name, ft_strlen(name)) == 0)
			return (i);
		i++;
	}
	return (-1);
}
char	**realloc_envv(char **env, int new_size)
{
	char	**new;
	int		i;

	new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1));
	i = -1;
	while (env[++i] && i < new_size)
	{
		new[i] = ft_strdup(env[i]);
		free(env[i]);
	}
	free(env);
	return (new);
}
char	**set_env_var(char **env, char *key, char *value)
{
	int		pos;
	char	*tmp;

	pos = ft_env_index(env, key);
	tmp = ft_strjoin("=", value);
	if (env[pos])
	{
		free(env[pos]);
		if (value)
			env[pos] = ft_strjoin(key, tmp);
		else
			env[pos] = ft_strjoin(key, "=");
	}
	else
	{
		env = realloc_envv(env, pos + 1);
		if (value)
			env[pos] = ft_strjoin(key, tmp);
		else
			env[pos] = ft_strjoin(key, "=");
	}
	free(tmp);
	return (env);
}

char **ft_set_env_var(char **env, int i, char *value)
{
	char *str;
	char *temp;
	int j;

	str = ft_strnew(ft_strlen(env[i] + ft_strlen(value)));
	j = 0;
	while (env[i][j] != '=' && env[i][j] != '\0')
	{
		str[j] = env[i][j];
		j++;
	}
	str[j] = env[i][j];
	temp = ft_strjoin(str, value);
	free(env[i]);
	free(str);
	env[i] = NULL;
	env[i] = temp;;
	return (env);
}
void	ft_new_env_var()
{
	return ;
}
void	ft_setenv(char **env, char *str)
{
	char **args;
	int index;

	args = ft_strsplit(str, ' ');
	ft_printf("args:%s %s\n", args[1], args[2]);
	if ((index = ft_env_index(env, args[1])) == -1)
		ft_new_env_var();
	else
		env = set_env_var(env, args[1], args[2]);
		//env = ft_set_env_var(env, index, args[2]);
	return ;
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
		else if (ft_strncmp(commands[i], "setenv ", 7) == 0)
			ft_setenv(env, commands[i]);
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
			ft_del(commands, str, env);
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
