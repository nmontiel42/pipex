/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:23:33 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/17 15:01:10 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		file1;
	int		file2;
	char	**env;
	char	***cmd;
}				t_data;

void	start_program(t_data *data);
int		obtain_comands(int argc, char **argv, t_data *data);
int		main(int argc, char **argv, char **env);
int		new_split(t_data *data, char **env);
void	free_all(t_data *data);

#endif