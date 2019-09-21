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

void	ft_cd_to_path(char *path, t_shell *shell)
{
	char	*here;
	char	*temp;
	char	buff[4001];

	here = getcwd(buff, 4000);
	if (chdir(path) == 0)
	{
		temp = ft_strjoin("setenv OLDPWD ", here);
		ft_setenv(shell, temp);
		free(shell->oldpwd);
		shell->oldpwd = ft_strdup(here);
		free(temp);
		temp = ft_strjoin("setenv PWD ", path);
		ft_setenv(shell, temp);
		free(temp);
		free(shell->pwd);
		shell->pwd = ft_strdup(path);
	}
	else
		ft_printf("%s: No such file or directory.\n", path);
}

void	ft_cd(char *str, t_shell *shell)
{
	char **args;
	char *oldpath;

	args = ft_strsplit_wide(str, ' ');
	if (args[0][2] != '\0')
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(args[0]);
	}
	else if (args[1] != 0 && args[2] != 0)
	{
		ft_putendl("cd: Too many arguments.");
	}
	else if (args[1] == 0 || (ft_strncmp(args[1], "--", 2) == 0
		&& args[1][2] == '\0') || (ft_strncmp(args[1], "~", 1) == 0
			&& args[1][1] == '\0'))
		ft_cd_to_path(shell->home, shell);
	else if (ft_strncmp(args[1], "-", 1) == 0 && args[1][1] == '\0')
		ft_cd_to_path(shell->oldpwd, shell);
	else
		ft_cd_to_path(args[1], shell);
	ft_free_mas(args);
}
