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

void	ft_run_bin(char *lock, char **args, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		execve(lock, args, env);
	wait(&pid);
}

int		run_bin_and_free(char **args, t_shell *shell, char **path, char *lock)
{
	ft_run_bin(args[0], args, shell->env);
	ft_free_mas(args);
	ft_free_mas(path);
	free(lock);
	return (1);
}

int		run_bin_and_free2(char **args, t_shell *shell, char **path, char *lock)
{
	ft_run_bin(lock, args, shell->env);
	ft_free_mas(args);
	ft_free_mas(path);
	free(lock);
	return (1);
}

int		check_bins_in_path(t_shell *shell, char **args, int index)
{
	int			i;
	char		**path;
	char		*temp;
	char		*lock;
	struct stat	bin_stat;

	path = ft_strsplit_wide(shell->env[index], ':');
	i = 0;
	while (path[i] != 0)
	{
		temp = ft_strjoin(path[i], "/");
		lock = ft_strjoin(temp, args[0]);
		free(temp);
		if (lstat(args[0], &bin_stat) != -1)
			return (run_bin_and_free(args, shell, path, lock));
		else if (lstat(lock, &bin_stat) != -1)
			return (run_bin_and_free2(args, shell, path, lock));
		i++;
		free(lock);
	}
	ft_free_mas(args);
	ft_free_mas(path);
	return (-1);
}

int		check_bin_in_path_and_run(t_shell *shell, char *str)
{
	int			index;
	char		**args;
	struct stat	bin_stat;

	args = ft_strsplit_wide(str, ' ');
	if ((index = ft_find_env_var(shell->env, "PATH")) == -1)
	{
		if (lstat(args[0], &bin_stat) != -1)
		{
			ft_run_bin(args[0], args, shell->env);
			ft_free_mas(args);
			return (1);
		}
		ft_free_mas(args);
		return (-1);
	}
	if (check_bins_in_path(shell, args, index) == 1)
		return (1);
	return (-1);
}
