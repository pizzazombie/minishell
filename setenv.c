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

char	**realloc_envv(char **env, int new_size)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (new_size + 1));
	i = -1;
	while (env[++i] && i < new_size)
	{
		new[i] = ft_strdup(env[i]);
		free(env[i]);
	}
	free(env);
	return (new);
}

char	**set_env_var(t_shell *shell, char *name, char *value)
{
	int		pos;
	char	*tmp;

	pos = ft_env_index(shell->env, name);
	tmp = ft_strjoin("=", value);
	if (shell->env[pos])
	{
		
		free(shell->env[pos]);
		if (value)
			shell->env[pos] = ft_strjoin(name, tmp);
		else
			shell->env[pos] = ft_strjoin(name, "=");
	}
	else
	{
		shell->env = realloc_envv(shell->env, pos + 1);
		shell->env_vars++;
		if (value)
			shell->env[pos] = ft_strjoin(name, tmp);
		else
			shell->env[pos] = ft_strjoin(name, "=");
		ft_printf("%s variable done\n", name);
	}
	free(tmp);
	return (shell->env);
}

void	ft_setenv(t_shell *shell, char *str)
{
	char **args;
	int index;

	args = ft_strsplit_wide(str, ' ');
	if (args[0][6] == '\0' && args[1] == 0)
	{
		ft_env(shell, "env");
		ft_free_mas(args);
		return ;
	}
	
	if (args[0][6] != '\0' && args[0][6] != ' ')
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(args[0]);
	}
	else
		shell->env = set_env_var(shell, args[1], args[2]);
	
		//env = ft_set_env_var(env, index, args[2]);
	ft_free_mas(args);
	return ;
}
