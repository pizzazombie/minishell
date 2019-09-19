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

void	ft_cd(char *str)
{
	ft_putchar('\n');
}
void	ft_echo(char *str)
{
	int i;
	int j;
	char **args;

	i = 0;
	args = ft_strsplit_wide(str, ' ');
	while (args[i] != 0)
	{
		j = 0;
		while (args[i][j] == ' ')
		{
			j++;
		}
		ft_putstr(args[i] + j);
		ft_putchar('\n');
		i++;
	}
	ft_free_mas(args);
}
void	ft_pwd(char *str, t_shell *shell)
{
	char **args = ft_strsplit_wide(str, ' ');

	if (args[1] != 0)
		ft_putstr("pwd: too many arguments\n");
	else
	{
		ft_printf("%s\n", shell->location);
	}
	
}
void	ft_env(t_shell *shell, char *str)
{
	char **args;

	
	if (str[3] == '\0' || str[3] == ';')
	{
		ft_print_env(shell);
		
	}
	else
	{
		args = ft_strsplit_wide(str, ' ');
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
		ft_free_mas(args);
	}
	
}
