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

int		ft_run_commands(char **commands, t_shell *shell)
{
	int i;

	i = 0;
	while (commands[i] != 0)
	{
		if (ft_strncmp(commands[i], "exit", 4) == 0
			&& ft_exit(commands[i]) == 1)
			return (1);
		else if (ft_strncmp(commands[i], "echo", 4) == 0)
			ft_echo(commands[i]);
		else if (ft_strncmp(commands[i], "cd", 2) == 0)
			ft_cd(commands[i], shell);
		else if (ft_strncmp(commands[i], "setenv ", 6) == 0)
			ft_setenv(shell, commands[i]);
		else if (ft_strncmp(commands[i], "unsetenv", 8) == 0)
			ft_unsetenv(shell, commands[i]);
		else if (ft_strncmp(commands[i], "env", 3) == 0)
			ft_env(shell, commands[i]);
		else if (ft_strncmp(commands[i], "prompt", 6) == 0)
			ft_change_prompt(shell);
		else if (check_bin_in_path_and_run(shell, commands[i]) == -1)
			ft_command_not_found(commands[i]);
		i++;
	}
	return (0);
}
