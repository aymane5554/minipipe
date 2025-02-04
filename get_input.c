/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:25:36 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/02/04 10:03:16 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	*get_input(char	**argv)
{
	int		limiter_len;
	char	*line;
	char	*input;
	char	*tmp;
	char	*tmp2;

	input = NULL;
	limiter_len = ft_strlen(argv[2]);
	line = get_next_line(0);
	while (ft_strncmp(line, argv[2], limiter_len))
	{
		tmp = line;
		tmp2 = input;
		input = ft_strjoin(input, line);
		free(tmp2);
		free(tmp);
		line = get_next_line(0);
	}
	free(line);
	return (input);
}

void	execute3(int fds[2], int pfd[2], char ***cmds_args, char **argv)
{
	int		pfd2[2];
	char	*input;

	input = get_input(argv);
	pipe(pfd2);
	if (input)
		write(pfd2[1], input, ft_strlen(input));
	free(input);
	close(pfd2[1]);
	if (fork() == 0)
	{
		dup2(pfd2[0], 0);
		dup2(pfd[1], 1);
		close(pfd[1]);
		close(pfd2[0]);
		execve(cmds_args[0][0], cmds_args[0], NULL);
		perror("execve\n");
		exit(1);
	}
	close(pfd2[0]);
}
