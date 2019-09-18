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


void	ft_remove_var(t_shell *shell, char *name)
{
	int index;
	int i;
	char **new_env;

	if ((index = ft_find_env_var(shell->env, name)) != -1)
	{
		new_env = (char **)malloc(sizeof(char *) * (shell->env_vars - 1));
		i = 0;
		while (i < index)
		{
			new_env[i] = ft_strdup(shell->env[i]);
			free(shell->env[i]);
			i++;
		}
		free(shell->env[i]);
		i++;
		while (shell->env[i] != 0)
		{
			new_env[i - 1] = ft_strdup(shell->env[i]);
			free(shell->env[i]);
			i++;
		}
		new_env[i - 1] = 0;
		free(shell->env);
		shell->env = new_env;
		shell->env_vars--;
	}
}
void	ft_unsetenv(t_shell *shell, char *str)
{
	char **args;
	int i;

	args = ft_strsplit(str, ' ');
	i = 1;
	if (args[1] == 0)
		ft_putendl("unsetenv: Too few arguments.");
	else
	{
		while (args[i] != 0)
		{
			ft_remove_var(shell, args[i]);
			i++;
		}
	}
	ft_free_mas(args);
	
}
