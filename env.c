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

void		remove_env_var(int pos, char **env)
{
	free(env[pos]);
	env[pos] = NULL;
	env[pos] = ft_memalloc(2);
}
char	*get_env_var(char **env, char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		tmp = ft_strjoin(var, "=");
		if (ft_strncmp(env[i], tmp, ft_strlen(tmp)))
		{
			free(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
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
		args = ft_strsplit(str, ' ');
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
int	ft_find_env_var(char **env, char *name)
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
	ft_printf("No env var finded with name %s\n", name);
	free(temp);
	return (-1);
}
char	**realloc_envv(char **env, int new_size)
{
	char	**new;
	int		i;

	new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1));
	i = -1;
	while (env[++i] && i < new_size)
	{
		new[i] = ft_strdup(env[i]);
		free(env[i]);
	}
	free(env);
	return (new);
}
char	**set_env_var(t_shell *shell, char *key, char *value)
{
	int		pos;
	char	*tmp;

	pos = ft_env_index(shell->env, key);
	tmp = ft_strjoin("=", value);
	if (shell->env[pos])
	{
		free(shell->env[pos]);
		if (value)
			shell->env[pos] = ft_strjoin(key, tmp);
		else
			shell->env[pos] = ft_strjoin(key, "=");
	}
	else
	{
		shell->env = realloc_envv(shell->env, pos + 1);
		
		if (value)
			shell->env[pos] = ft_strjoin(key, tmp);
		else
			shell->env[pos] = ft_strjoin(key, "=");
		ft_printf("%s variable done\n", key);
	}
	free(tmp);
	return (shell->env);
}

/*char **ft_set_env_var(char **env, int i, char *value)
{
	char *str;
	char *temp;
	int j;

	str = ft_strnew(ft_strlen(env[i] + ft_strlen(value)));
	j = 0;
	while (env[i][j] != '=' && env[i][j] != '\0')
	{
		str[j] = env[i][j];
		j++;
	}
	str[j] = env[i][j];
	temp = ft_strjoin(str, value);
	free(env[i]);
	free(str);
	env[i] = NULL;
	env[i] = temp;;
	return (env);
}*/
void	ft_new_env_var()
{
	return ;
}


void	ft_setenv(t_shell *shell, char *str)
{
	char **args;
	int index;

	args = ft_strsplit(str, ' ');
//	ft_printf("args:%s %s\n", args[1], args[2]);
/*	if ((index = ft_find_env_var(shell->env, args[1])) == -1)
		ft_new_env_var();
	else*/
		shell->env = set_env_var(shell, args[1], args[2]);
		//env = ft_set_env_var(env, index, args[2]);
	ft_free_mas(args);
	return ;
}
