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
		free(shell->env[i]);
		i++;
	}
	free(shell->env);
	free(shell->home);
	free(shell->pwd);
	free(shell->oldpwd);
}

void	ft_init_shell(t_shell *shell)
{
	shell->location = NULL;
	shell->env = NULL;
	shell->env_vars = 0;
	shell->prmpt = 0;
	g_prompt = "(つಠ ʖ̯ ಠ)つ";
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
}

char	**ft_init_env(char **environ, t_shell *shell)
{
	char	**env;
	int		i;

	i = 0;
	env = (char **)malloc(sizeof(char *) * (ft_env_len(environ) + 1));
	while (environ[i] != 0)
	{
		if ((env[i] = ft_strdup(environ[i])) == NULL)
			return (NULL);
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			env[i][6] = env[i][6] + 1;
		i++;
	}
	shell->env_vars = i;
	env[i] = 0;
	shell->pwd = ft_strdup(get_env_var(environ, "PWD"));
	shell->home = ft_strdup(get_env_var(environ, "HOME"));
	shell->oldpwd = ft_strdup(shell->home);
	return (env);
}
