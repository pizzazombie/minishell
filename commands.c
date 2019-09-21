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


void	ft_echo(char *str1)
{
	int i;
	int j;
	char *str;
	char **args;
	int index;

	i = 0;
	index = 0;
	str = ft_brakets(ft_strdup(str1));
	args = ft_strsplit_wide(str, ' ');
	if (ft_strncmp(args[0], "-n", 2) == 0 && args[0][2] == '\0')
	{
		i++;
		index++;
	}
	while (args[i] != 0)
	{
		j = 0;
		while (args[i][j] == ' ')
		{
			j++;
		}
		ft_putstr(args[i] + j);
		ft_putchar(' ');
		i++;
	}
	if (index == 0)
		ft_putchar('\n');
	ft_free_mas(args);
	free(str);
	
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
