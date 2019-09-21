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

int		ft_check_name_length(char *str)
{
	int i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		i++;
	return (i);
}

char	*ft_new_var_name(char *str, int i)
{
	char	*name;
	int		j;

	j = 0;
	name = ft_strnew(ft_check_name_length(str + i));
	while (str[i] != ' ' && str[i] != '\0')
	{
		name[j] = str[i];
		j++;
		i++;
	}
	return (name);
}

char	*ft_no_name_in_env(char *str, int ii)
{
	char	*temp;
	char	*temp2;

	str[ii] = '\0';
	temp = ft_strdup(str);
	str[ii] = '$';
	ii++;
	while (str[ii] != ' ' && str[ii] != '\0')
		ii++;
	temp2 = ft_strjoin(temp, str + ii);
	free(str);
	str = temp2;
	free(temp);
	return (str);
}

char	*ft_name_in_env(char *str, int ii, t_shell *shell, int index)
{
	char	*temp;
	char	*temp2;

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
	return (str);
}

char	*ft_parse_input(t_shell *shell, char *str)
{
	int		i;
	int		ii;
	char	*name;

	i = 0;
	while (str[i] != '\0')
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0')
		{
			ii = i;
			i++;
			name = ft_new_var_name(str, i);
			if ((ft_find_env_var(shell->env, name)) == -1)
				str = ft_no_name_in_env(str, ii);
			else
				str = ft_name_in_env(str, ii,
					shell, ft_find_env_var(shell->env, name));
			i = 0;
			free(name);
			continue ;
		}
		else
			i++;
	return (str);
}
