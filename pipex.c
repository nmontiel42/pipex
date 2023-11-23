/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:14:40 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/23 15:39:55 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	start_program(t_data *data)
{
	data->file1 = 0;
	data->file2 = 0;
	data->i = 0;
	data->j = 0;
	data->path = NULL;
	data->temp = NULL;
	data->temp_path = NULL;
	data->env = NULL;
	data->cmd = NULL;
	data->flag_hd = 0;
	data->line = NULL;
	data->fd = 0;
}

void	child_process(int *end, t_data *data)
{
	close(end[1]);
	if (dup2(end[0], STDIN_FILENO) == -1)
		ft_error("Error de stdin child");
	if (dup2(data->file2, STDOUT_FILENO) == -1)
		ft_error("Error de stdout child");
	close(data->file2);
	if (execve(data->path[1], data->cmd[1], NULL) == -1)
		ft_error("Error de execve child");
}

int	obtain_comands(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	data->cmd = ft_calloc(argc - 2, sizeof(char **));
	while (i < argc - 2 && j < argc - 1)
	{
		data->cmd[i] = new_split_version(argv[j], ' ');
		if (data->cmd[i] == NULL)
			return (EXIT_FAILURE);
		i++;
		j++;
	}
	data->cmd[i] = NULL;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		i;

	if (argc == 5)
	{
		data = ft_calloc(1, sizeof(t_data));
		start_program(data);
		data->file1 = open(argv[1], O_RDONLY);
		if (data->file1 == -1)
			perror("Error file1");
		data->file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->file2 == -1)
			perror("Error file2");
		if (new_split(data, env) == 1)
			return (free_all(data), EXIT_FAILURE);
		if (obtain_comands(argc, argv, data) == 1)
			return (free_all(data), EXIT_FAILURE);
		if (ft_check(data, argc - 2) == 1)
			return (free_all(data), EXIT_FAILURE);
		ft_exec(data);
		free_all(data);
		return (EXIT_SUCCESS);
	}
	ft_error("Error de argumentos");
}
