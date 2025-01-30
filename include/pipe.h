/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:30:34 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/29 09:06:37 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line.h"

char	*get_input(char	**argv);
void	execute3(int fds[2], int pfd[2], char ***cmds_args, char **argv);
int		cmds_number(char ***cmds_args);
void	allocate(char ****cmds_args, char is_here, int argc, char **argv);
void	check_files(int argc, char **argv, int fds[2]);
int		find_path_var(char **env);
char	*check_commands(char **env, char *cmd);
void	free_dbl_ptr(char **ptr, int i);
int		valid_quotes(char	*str);
void	free_trpl_ptr(char ***ptr, int i);
#endif
