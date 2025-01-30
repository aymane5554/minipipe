/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:40:21 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/30 20:30:19 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	epilogue(int fds[2], int pfd[2], char ***cmds_args)
{
	int	i;

	i = 0;
	close(fds[0]);
	close(fds[1]);
	close(pfd[0]);
	close(pfd[1]);
	while (cmds_args[i] != NULL)
	{
		free_dbl_ptr(cmds_args[i], 0);
		i++;
	}
	free(cmds_args);
}

void	prologue(int argc, char **argv, char **env, char ***cmds_args)
{
	char	*tmp;
	int		i;
	int		offset;

	if (ft_strncmp("here_doc", argv[1], 8) == 0)
		i = 3;
	else
		i = 2;
	offset = i;
	while (i <= argc - 2)
	{
		if (valid_quotes(argv[i]) == 0)
			return (perror("Invalid quotes"), exit(1));
		cmds_args[i - offset] = ft_split(argv[i], ' ');
		tmp = cmds_args[i - offset][0];
		cmds_args[i - offset][0]
			= check_commands(env, cmds_args[i - offset][0]);
		free(tmp);
		if (cmds_args[i - offset][0] == NULL)
			return (free_trpl_ptr(cmds_args, 0), perror(tmp), exit(1));
		i++;
	}
}

void	execute2(int fds[2], int pfd[2], char ***cmds_args, int nth)
{
	int		pfd2[2];

	pfd2[0] = pfd[0];
	pfd2[1] = pfd[1];
	close(pfd[1]);
	pipe(pfd);
	if (fork() == 0)
	{
		dup2(pfd2[0], 0);
		dup2(pfd[1], 1);
		close(pfd2[0]);
		close(pfd[1]);
		execve(cmds_args[nth][0], cmds_args[nth], NULL);
		perror("execve\n");
		exit(1);
	}
	close(pfd2[0]);
}

void	execute(int fds[2], int pfd[2], char ***cmds_args, int nth)
{
	if (nth == 0)
	{
		if (fork() == 0)
		{
			dup2(fds[0], 0);
			dup2(pfd[1], 1);
			close(fds[0]);
			close(pfd[1]);
			execve(cmds_args[0][0], cmds_args[0], NULL);
			return (perror("execve"), exit(1));
		}
	}
	else if (nth == cmds_number(cmds_args) - 1)
	{
		close(pfd[1]);
		if (fork() == 0)
		{
			dup2(pfd[0], 0);
			dup2(fds[1], 1);
			close(fds[1]);
			close(pfd[0]);
			execve(cmds_args[nth][0], cmds_args[nth], NULL);
			return (perror("execve"), exit(1));
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	int		fds[2];
	char	***cmds_args;
	int		status;
	int		pfd[2];
	int		i;

	if (argc == 1)
		exit(1);
	pipe(pfd);
	i = 1;
	check_files(argc, argv, fds);
	allocate(&cmds_args, ft_strncmp("here_doc", argv[1], 8), argc, argv);
	prologue(argc, argv, env, cmds_args);
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
		execute3(fds, pfd, cmds_args, argv);
	else
		execute(fds, pfd, cmds_args, 0);
	while (i < cmds_number(cmds_args) - 1)
	{
		wait(&status);
		execute2(fds, pfd, cmds_args, i);
		i++;
	}
	wait(&status);
	execute(fds, pfd, cmds_args, i);
	return (epilogue(fds, pfd, cmds_args), 0);
}
