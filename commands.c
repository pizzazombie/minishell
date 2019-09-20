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
	char *temp;
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
	{
		ft_printf("%s: No such file or directory.\n", path);
	}
	
}
void	ft_cd(char *str, t_shell *shell)
{
	char **args;
	char *path;
	char *oldpath;

	args = ft_strsplit_wide(str, ' ');
	//path = get_env_var(shell->env, "PWD");
	//oldpath = get_env_var(shell->env, "PWD");
	if (args[0][2] != '\0')
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(args[0]);
		ft_free_mas(args);
		return ;
	}
	else if (args[1] != 0 && args[2] != 0)
	{
		ft_putendl("cd: Too many arguments.");
		ft_free_mas(args);
		return ;
	}
	else if (args[1] == 0 || (ft_strncmp(args[1], "--", 2) == 0 && args[1][2] == '\0') || (ft_strncmp(args[1], "~", 1) == 0 && args[1][1] == '\0'))
	{
		ft_cd_to_path(shell->home, shell);
	}
	else if (ft_strncmp(args[1], "-", 1) == 0 && args[1][1] == '\0')
		ft_cd_to_path(shell->oldpwd, shell);
	else
	{
		ft_cd_to_path(args[1], shell);
	}
	//ft_putchar('\n');
}
int ft_str_len_without_br(char *str)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
			k++;
		i++;
	}
	return (i - k);
}
char *ft_brakets(char *str)
{
	int i;
	int k;
	char *temp;

	i = 0;
	k = 0;
	temp = ft_strnew(ft_str_len_without_br(str));
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
			i++;
		else
		{
			temp[k] = str[i];
			k++;
			i++;
		}
	}
	//free(str);
	return (temp);
}
void	ft_echo(char *str1)
{
	int i;
	int j;
	char *str;
	char **args;
	int index;

	i = 0;
	index = 0;
	str = ft_brakets(str1);
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
