/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:29:51 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/23 13:19:35 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
	close(end[0]);
	if (dup2(end[1], STDOUT_FILENO) == -1)
		ft_error2("Error de stdin child", data->flag_hd);
	if (execve(data->path[data->i], data->cmd[data->i], NULL) == -1)
		ft_error2("Error de execve child2", data->flag_hd);
}

int	obtain_comands(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (data->flag_hd)
		j = 3;
	else
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

int	get_here_doc(char *argv, t_data *data)
{
	if (ft_strncmp(argv, "here_doc", 8) == 0)
		return (data->flag_hd = 1, 6);
	return (5);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		i;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		ft_error2("Error al asignar memoria", data->flag_hd);
	start_program(data);
	if (argc >= get_here_doc(argv[1], data))
	{
		if (new_split(data, env) == 1)
			return (free_all(data), EXIT_FAILURE);
		if (obtain_comands(argc, argv, data) == 1)
			return (free_all(data), EXIT_FAILURE);
		if (ft_check(data, argc - 2) == 1)
			return (free_all(data), EXIT_FAILURE);
		ft_exec2(data, argc, argv);
		free_all(data);
		return (EXIT_SUCCESS);
	}
	free_all(data);
	return (EXIT_FAILURE);
}
