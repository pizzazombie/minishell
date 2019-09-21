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

int		ft_env_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != 0)
		i++;
	return (i);
}

void	ft_copy_env(char **new_env, t_shell *shell, int *i, int *j)
{
	new_env[*i] = ft_strdup(shell->env[*j]);
	free(shell->env[*j]);
	*i = *i + 1;
	*j = *j + 1;
}

char	**ft_remove_var(t_shell *shell, char *name)
{
	int		index;
	int		i;
	int		j;
	char	**new_env;

	if ((index = ft_find_env_var(shell->env, name)) != -1)
	{
		new_env = (char **)malloc(sizeof(char *) * (ft_env_len(shell->env)));
		i = 0;
		j = 0;
		while (i < index)
			ft_copy_env(new_env, shell, &i, &j);
		free(shell->env[j]);
		j++;
		while (shell->env[j] != 0)
			ft_copy_env(new_env, shell, &i, &j);
		new_env[i] = 0;
		free(shell->env);
		shell->env_vars--;
		return (new_env);
	}
	else
		return (shell->env);
}

void	ft_remove_var22(t_shell *shell, char *name)
{
	int		index;
	int		i;
	char	**new_env;

	if ((index = ft_find_env_var(shell->env, name)) != -1)
	{
		free(shell->env[index]);
		shell->env[index] = 0;
	}
}

void	ft_unsetenv(t_shell *shell, char *str)
{
	char	**args;
	int		i;

	args = ft_strsplit_wide(str, ' ');
	i = 1;
	if (args[0][8] == '\0' || args[0][8] == ' ')
	{
		if (args[1] == 0)
			ft_putendl("unsetenv: Too few arguments.");
		else
		{
			while (args[i] != 0)
			{
				shell->env = ft_remove_var(shell, args[i]);
				i++;
			}
		}
	}
	else
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(args[0]);
	}
	ft_free_mas(args);
}
