/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:14:40 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/17 13:22:07 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	start_program(t_data *data)
{
	data->file1 = 0;
	data->file2 = 0;
	data->env = NULL;
	data->cmd = NULL;
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
		data->cmd[i] = ft_split(argv[j], ' ');
		if (data->cmd[i] == NULL)
			return (EXIT_FAILURE);
		i++;
		j++;
	}
	data->cmd = NULL;
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
		new_split(data, env);
		obtain_comands(argc, argv, data);
		/*i = -1;
		while ((data->env)[++i])
		{
			ft_printf("%s\n", (data->env)[i]);
		}*/
	}
}
