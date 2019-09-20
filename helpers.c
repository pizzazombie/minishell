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

//	ft_printf("i'm in disp\n");
	str = getcwd(buf, 4000);
	ft_printf("\033[34;1;1m%s\033[0m", str);
	ft_putstr("(つಠ ʖ̯ ಠ)つ");
	//shell->location = str;
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

void	ft_del(char **arr, char *str, t_shell *shell)
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
	while (shell->env[i] != 0)
	{
//		printf("фришу %d строку с именем %s\n", i, shell->env[i]);
		free(shell->env[i]);
		
		i++;
	}
	free(shell->env);
	free(shell->home);
	free(shell->pwd);
	free(shell->oldpwd);	//make
//	if (shell != NULL)
//		free(shell);
}

void	ft_init_shell(t_shell *shell)
{
	//shell = (t_shell *)malloc(sizeof(shell));
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
//	ft_printf("i'm in init env\n");
	env = (char **)malloc(sizeof(char *) * ft_env_len(environ));
//	printf("before cycle\n");
	while (environ[i] != 0)
	{
//		ft_printf("cycle %d\n", i);
		if ((env[i] = ft_strdup(environ[i])) == NULL)
			return (NULL);
		i++;
	}
	shell->env_vars	= i;
	env[i] = 0;
	shell->pwd = ft_strdup(get_env_var(environ, "PWD"));
	shell->home = ft_strdup(get_env_var(environ, "HOME"));
//	printf("home=%s\n", shell->home);
	shell->oldpwd = ft_strdup(shell->home);
//	ft_printf("init env end\n");
	return (env);
}
