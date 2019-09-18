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

void		remove_env_var(int pos, char **env)
{
	free(env[pos]);
	env[pos] = NULL;
	env[pos] = ft_memalloc(2);
}
void	ft_remove_var(t_shell *shell, char *name)
{
	int index;
	int i;
	char **new_env;

	if ((index = ft_find_env_var(shell->env, name)) != -1)
	{
		new_env = (char **)ft_memalloc(sizeof(char *) * (shell->env_vars - 1));
	i = 0;
	while (i < index)
	{
		new_env[i] = ft_strdup(shell->env[i]);
		free(shell->env[i]);
	}
	free(shell->env[i]);
	i++;
	while (i <= shell->env_vars)
	{
		new_env[i - 1] = ft_strdup(shell->env[i]);
		i++;
	}
	new_env[i - 1] = 0;
	free(shell->env);
	shell->env = new_env;
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
		}
	}
	
}
