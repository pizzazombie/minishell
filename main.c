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

#include <stdio.h>
#include "shell.h"

void	ft_display_path(void)
{
	char *str;
	char buf[4001];
	char *p;

	str = getcwd(buf, 4000);
	ft_printf("\033[34;1;1m%s\033[0m", str);
	ft_putstr(">");
	//free(str);
}

int main(int ac, char **av)
{
	char *str;
	
	str = ft_strnew(100);
	while (1)
	{
		ft_display_path();
		get_next_line(0, &str);
		if (ft_strcmp(str, "exit") == 0)
			exit (1);
		else if (ft_strncmp(str, "echo ", 5) == 0)
			ft_putstr(str + 5);
		//ft_putchar('\n');
		else
			ft_putstr(str);
		ft_putchar('\n');
		//ft_get_input()
		
	}
	return (0);
}
