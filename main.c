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

int	ft_check_name_length(char *str)
{
	int i;
	
	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	return (i);
}
char *ft_parse_input(t_shell *shell, char *str)
{
	int i;
	int j;
	int ii;
	int index;
	char *temp;
	char *temp2;
	char *name;

	i = 0;
	ii = 0;
	//temp2 = ft_strnew(1);
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0')
		{
			ii = i;
			i++;
			j = 0;
			name = ft_strnew(ft_check_name_length(str + i));
			while (str[i] != ' ' && str[i] != '\0')
			{
				name[j] = str[i];
				j++;
				i++;
			}
			if ((index = ft_find_env_var(shell->env, name)) == -1)
			{
				str[ii] = '\0';

				temp = ft_strdup(str);
				ii++;
				while (str[ii] != ' ' && str[ii] != '\0')
					ii++;
				temp2 = ft_strjoin(temp, str + ii);
				free(str);
				str = temp2;
				free(temp);
				i = 0;
				free(name);
				continue ;
			}
			else
			{
				str[ii] = '\0';

				temp = ft_strdup(str);
				ii++;
				while (str[ii] != ' ' && str[ii] != '\0')
					ii++;
				temp2 = ft_strjoin(temp, ft_strchr(shell->env[index], '=') + 1);
				free(temp);
				temp = ft_strjoin(temp2, str + ii);
				free(temp2);
				str = temp;
				i = 0;
				free(name);
				continue ;
			}
		}
/*		else if (str[i] == '~')
		{
			temp = ft_strjoin()
		}*/
		else
		{
			i++;
		}
		
	}
	return (str);
}
int main(int ac, char **av, char **environ)
{
	char *str;
	char **commands;
	//char **env;

	t_shell shell;

//	ft_printf("first\n");
	ft_init_shell(&shell);
//	ft_printf("after init shell\n");
	if ((shell.env = ft_init_env(environ, &shell)) == NULL)
		return (1);
	//str = ft_strnew(100);
//	ft_printf("WOWOWO1\n");
	while (1)
	{
	//	ft_printf("before disp\n");
		ft_display_path(&shell);
		get_next_line(0, &str);
		str = ft_parse_input(&shell, str);
//		ft_printf("%s\n", str);
		commands = ft_strsplit_wide(str, ';');
//		ft_printf("before run cmnds\n");
		if (ft_run_commands(commands, &shell) == 1)
		{
			ft_del(commands, str, &shell);
		//	ft_printf("WOWOWO\n");
			//free(&shell); why abort???(
			return (0);
		}
		else
		{
			ft_free_mas(commands);
			free(str);
			continue ;
		}
		
		
		//ft_get_input()
		
	}
	return (0);
}
