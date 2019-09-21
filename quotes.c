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

int		ft_str_len_without_br(char *str)
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

char	*ft_brakets(char *str)
{
	int		i;
	int		k;
	char	*temp;

	i = 0;
	k = 0;
	//if (ft_strchr(str, 34) == NULL && (ft_strchr(str, 39) == 0))
	//	return (str);
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
	free(str);
	return (temp);
}

int		ft_is_qoute(char *str)
{
	int i;
	int q;
	int q2;

	i = 0;
	q = 0;
	q2 = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39)
			q++;
		else if (str[i] == 34)
			q2++;
		i++;
	}
	if ((q + 2) % 2 == 0 && (q2 + 2) % 2 == 0)
		return (1);
	else
	{
		if (q % 2 != 0)
			return (-39);
		if (q2 % 2 != 0)
			return (-34);
	}
	return (-2);
}

char	*ft_put_n(char *str)
{
	char *temp;

	temp = ft_strjoin(str, "\n");
	free(str);
	return (temp);
}

char	*ft_qoute(char *str_or)
{
	char	*str1;
	char	*temp;
	char	*str;
	int		q;

	q = (-1) * ft_is_qoute(str_or);
	str = ft_strdup(str_or);
	free(str_or);
	q == 34 ? ft_putstr("dquote> ") : ft_putstr("quote> ");
	get_next_line(0, &str1);
	str = ft_put_n(str);
	while (ft_strchr(str1, q) == NULL)
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
