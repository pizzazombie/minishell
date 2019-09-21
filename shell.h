/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dholiday <dholiday@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 13:53:13 by dholiday          #+#    #+#             */
/*   Updated: 2019/09/16 17:43:49 by dholiday         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <dirent.h>
# include <stdlib.h>
# include "Libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>

char				*g_prompt;

typedef struct		s_shell
{
	int				env_vars;
	int				prmpt;
	char			*location;
	char			*pwd;
	char			*oldpwd;
	char			*home;
	char			**env;
}					t_shell;

void				ft_print_env(t_shell *shell);
void				ft_display_path(t_shell *shell);
char				**ft_init_env(char **environ, t_shell *shell);
void				ft_free_mas(char **arr);
void				ft_del(char **arr, char *str, t_shell *shell);
void				ft_init_shell(t_shell *shell);
char				**ft_strsplit_wide(char const *str, char c);
int					ft_run_commands(char **commands, t_shell *shell);
int					ft_env_len(char **arr);
char				**ft_strsplit_for_echo(char const *str, char c);
char				*ft_qoute(char *str_or);
int					ft_is_qoute(char *str);
char				*ft_brakets(char *str);
void				ft_change_prompt(t_shell *shell);
/*
**  commands
*/
void				ft_cd(char *str, t_shell *shell);
void				ft_echo(char *str1);
void				ft_pwd(char *str, t_shell *shell);
void				ft_env(t_shell *shell, char *str);
void				ft_setenv(t_shell *shell, char *str);
void				ft_unsetenv(t_shell *shell, char *str);

/*
**  env
*/

char				**set_env_var(t_shell *shell, char *name, char *value);
int					ft_find_env_var(char **env, const char *name);
int					ft_env_index(char **env, char *name);
char				*get_env_var(char **env, char *var);

#endif
