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

int ft_env_len(char **arr)
{
	int i;
	i = 0;

	while (arr[i] != 0)
		i++;
	return (i);
}
char **ft_remove_var(t_shell *shell, char *name)
{
	int index;
	int i;
	int j;
	char **new_env;

	if ((index = ft_find_env_var(shell->env, name)) != -1)
	{
	//	printf("вделяем память под новый массив\n");
		new_env = (char **)malloc(sizeof(char *) * (ft_env_len(shell->env)));
		i = 0;
		j = 0;
		while (i < index)
		{
			new_env[i] = ft_strdup(shell->env[j]);
	//		printf("копирую и фришу строку %s\n", shell->env[j]);
			free(shell->env[j]);
			i++;
			j++;
		}
		//new_env[i] = ft_strdup(shell->env[j]);
		free(shell->env[j]);
		j++;
		//i--;
		while (shell->env[j] != 0)
		{
			new_env[i] = ft_strdup(shell->env[j]);
			free(shell->env[j]);
			i++;
			j++;
		}
		new_env[i] = 0;
		free(shell->env);
		
		shell->env_vars--;
		return (new_env);

	}
	else
	{
		return (shell->env);
	}
	
}
void	ft_remove_var22(t_shell *shell, char *name)
{
	int index;
	int i;
	char **new_env;

	if ((index = ft_find_env_var(shell->env, name)) != -1)
	{
		free(shell->env[index]);
		shell->env[index] = 0;
	}
}
void	ft_unsetenv(t_shell *shell, char *str)
{
	char **args;
	int i;

	args = ft_strsplit_wide(str, ' ');
	i = 1;
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
	ft_printf("удаление прошло успешно!\n");
	ft_free_mas(args);
	
}
