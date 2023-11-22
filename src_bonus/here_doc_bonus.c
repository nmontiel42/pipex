/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:58:02 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/22 16:03:31 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../libft/libft.h"

void	check_flag(int argc, char **argv, t_data *data)
{
	if (data->flag_hd == 1)
		here_doc(data, argc, argv);
	else
	{
		data->file1 = open(argv[1], O_RDONLY);
		data->file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->file1 == -1 || data->file2 == -1)
			ft_error2("Fallo de lectura bonus", data->flag_hd);
	}
}

void	here_doc(t_data *data, int argc, char **argv)
{
	data->file1 = open("here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->file1 == -1)
		ft_error2("Fallo de lectura de here_doc", data->flag_hd);
	data->fd = dup(STDIN_FILENO);
	while (1)
	{
		write(1, "here_doc> ", 10);
		data->line = get_next_line(data->fd);
		if (!data->line)
			ft_error2("Error de get_next_data->line", data->flag_hd);
		write(data->file1, data->line, ft_strlen(data->line));
		if (!ft_strncmp(argv[2], data->line, ft_strlen(argv[2])))
		{
			close(data->fd);
			get_next_line(data->fd);
			break ;
		}
		free(data->line);
	}
	close(data->file1);
	data->file1 = open("here_doc.tmp", O_RDONLY);
	data->file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->file1 == -1 || data->file2 == -1)
		ft_error2("Error de lecturaS bonus", data->flag_hd);
}

void	ft_exec2(t_data *data, int argc, char **argv)
{
	int		end[2];
	pid_t	child_pid;

	check_flag(argc, argv, data);
	if (dup2(data->file1, STDIN_FILENO) == -1)
		ft_error2("Error de stdin file1", data->flag_hd);
	data->i = -1;
	while (data->cmd[++data->i] != NULL)
	{
		if (pipe(end) == -1)
			ft_error2("Fallo de pipe", data->flag_hd);
		child_pid = fork();
		if (child_pid == -1)
			ft_error2("Fallo de child_pid", data->flag_hd);
		if (child_pid == 0)
		{
			if (data->cmd[data->i + 1] == NULL)
			{
				dup2(data->file2, STDOUT_FILENO);
				if (execve(data->path[data->i], data->cmd[data->i], NULL) == -1)
					ft_error2("Error de execve child", data->flag_hd);
				break ;
			}
			child_process(end, data);
		}
		else
		{
			waitpid(child_pid, NULL, 0);
			close(end[1]);
			if (dup2(end[0], STDIN_FILENO) == -1)
				ft_error2("Error de padre dup2", data->flag_hd);
		}
	}
}

