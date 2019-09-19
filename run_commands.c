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

void    ft_run_bin(char *lock, char **args, char **env)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
        execve(lock, args, env);
    wait(&pid);
}
int check_bin_in_path_and_run(t_shell *shell, char *str)
{
    int i;
    int index;
    char **args;
    char **path;
    char *lock;
    char *temp;
    struct stat bin_stat;


    args = ft_strsplit_wide(str, ' ');
    if ((index = ft_find_env_var(shell->env, "PATH")) == -1)
    {
        ft_free_mas(args);
        return (-1);
    }
 //   ft_printf("PATH=%s\n", shell->env[index]);
    path = ft_strsplit_wide(shell->env[index], ':');
    i = 0;
    while (path[i] != 0)
    {
        temp = ft_strjoin(path[i], "/");
        
        lock = ft_strjoin(temp, args[0]);
        free(temp);
 //       ft_printf("lock = %s\n", lock);
        if (lstat(lock, &bin_stat) != -1)
        {
 //           ft_printf("WEEEEEEE!!!!!! Find it!\n");
            ft_run_bin(lock, args, shell->env);
            
            return (1);
        }
        i++;
        free(lock);
    }
    ft_free_mas(args);
    return (-1);
}
int	ft_run_commands(char **commands, t_shell *shell)
{
	int i;

	i = 0;
	while (commands[i] != 0)
	{
		if (ft_strncmp(commands[i], "exit", 4) == 0)
		{
			return (1);
		}
		else if (ft_strncmp(commands[i], "echo ", 5) == 0)
			ft_echo(commands[i] + 5);
		else if (ft_strncmp(commands[i], "cd ", 3) == 0)
			ft_cd(commands[i]);
		else if (ft_strncmp(commands[i], "setenv ", 7) == 0)
			ft_setenv(shell, commands[i]);
		else if (ft_strncmp(commands[i], "unsetenv ", 8) == 0)
			ft_unsetenv(shell, commands[i]);
		else if (ft_strncmp(commands[i], "env", 3) == 0)
			ft_env(shell, commands[i]);
//		else if (ft_strncmp(commands[i], "pwd", 3) == 0)
//			ft_pwd(commands[i], shell);
        else if (check_bin_in_path_and_run(shell, commands[i]) == -1)
        {
			ft_putstr("minishell: command not found: ");
			ft_putendl(commands[i]);
		}
		//ft_putchar('\n');
/*		else
		{
			ft_putstr("minishell: command not found: ");
			ft_putendl(commands[i]);
		}*/
	//	ft_putchar('\n');
		i++;
	}
	return (0);
}