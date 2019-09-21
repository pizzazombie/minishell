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
int ft_is_qoute(char *str)
{
	int i;
	int q;

	i = 0;
	q = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34)
			q++;
		i++;
	}
	if (q % 2 == 0)
		return (1);
	else
	{
		return (-1);
	}
	
}
char *ft_put_n(char *str)
{
	char *temp;
	temp = ft_strjoin(str, "\n");
	free(str);
	return (temp);
}
char *ft_qoute(char *str_or)
{
	char *str1;
	char *temp;
	char *str;

	str = ft_strdup(str_or);
	ft_putstr("dquote> ");
	get_next_line(0, &str1);
	str = ft_put_n(str);
	while (ft_strchr(str1, 34) == NULL)
	{
		
		temp = ft_strjoin(str, str1);
		
		free(str1);
		free(str);
		str = temp;
		get_next_line(0, &str1);
		str = ft_put_n(str);
	}
	temp = ft_strjoin(str, str1);
		
		free(str1);
		free(str);
		str = temp;
	return (str);
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
	if (ft_is_qoute(str1) == -1)
		while (ft_is_qoute(str1) == -1)
		{
			str1 = ft_qoute(str1);
			str = ft_brakets(str1);
			free(str1);

		}
	else
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
