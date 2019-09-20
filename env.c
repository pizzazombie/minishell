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

char	*get_env_var(char **env, char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		tmp = ft_strjoin(var, "=");
		if (ft_strncmp(env[i], tmp, ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
}

int	ft_env_index(char **env, char *name)
{
	int i;
	char *temp;

	i = 0;
	temp = ft_strjoin(name, "=");
	while (env[i] != 0)
	{
		if (strncmp(env[i], temp, ft_strlen(name)) == 0)
		{
			free(temp);
			return (i);
		}
		i++;
	}
	free(temp);
	return (i);
}

int	ft_find_env_var(char **env, const char *name)
{
	int i;
	char *temp;

	i = 0;
	temp = ft_strjoin(name, "=");
	while (env[i] != 0)
	{
		if (strncmp(env[i], temp, ft_strlen(temp)) == 0)
		{
			free(temp);
			return (i);
		}
		i++;
	}
//	ft_printf("No env var finded with name %s\n", name);
	free(temp);
	return (-1);
}

void	ft_env(t_shell *shell, char *str)
{
	char **args;

	args = ft_strsplit_wide(str, ' ');

	if (args[0][3] == '\0' && args[1] == 0)
	{
		ft_print_env(shell);
		
	}
	else if (args[0][3] != '\0')
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(args[0]);
	}
	else
	{
		//args = ft_strsplit_wide(str, ' ');
		if (args[1])
		{
			if (args[2])
			{
				ft_putendl("setenv: Too many arguments.");
				ft_free_mas(args);
				return ;
			}
			ft_print_env(shell);
		}
		
	}
	ft_free_mas(args);
}
