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
	ft_putstr("(つಠ ʖ̯ ಠ)つ");
	shell->location = str;
	//free(str);
}

void	ft_free_mas(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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
	shell->env = NULL;
	shell->env_vars = 0;
}

void	ft_print_env(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->env[i] != 0)
	{
		ft_putendl(shell->env[i]);
		i++;
	}
//	ft_putstr("env printed!\n");
}

char **ft_init_env(char **environ, t_shell *shell)
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
	shell->env_vars	= i;
	env[i] = 0;
	return (env);
}
