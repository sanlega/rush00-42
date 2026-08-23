/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerodrig <cerodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:44:41 by cerodrig          #+#    #+#             */
/*   Updated: 2026/08/23 22:18:06 by salegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

char	**ft_split(char *str, char *charset);
int		ft_wordc(char *str, char *set);
int		ft_check(char **arr, int size, char *orig);
int		*ft_conform(char **nb, int size, int row);
void	ft_free_all(int **board, int rows, char **arr);
int		ft_solver(int **board, int size);

int	ft_check_spaces(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (str[0] == ' ')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
			return (0);
		i++;
	}
	if (i > 0 && str[i - 1] == ' ')
		return (0);
	return (1);
}

int	ft_initialize(int **board, char **arr, int size, int i)
{
	while (i < size)
	{
		board[i] = ft_conform(arr, size, i);
		if (!board[i])
		{
			ft_free_all(board, i, arr);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_args(int ac, char **av)
{
	if (ac != 2)
		return (0);
	if (!ft_check_spaces(av[1]))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	int		**board;
	int		size;
	char	**arr;

	i = 0;
	if (!ft_args(ac, av))
		return (write(1, "Error\n", 6), 1);
	size = (ft_wordc(av[1], " ")) / 4 + 2;
	arr = ft_split(av[1], " ");
	if (!arr || !ft_check(arr, (size - 2), av[1]))
		return (ft_free_all(NULL, 0, arr), write(1, "Error\n", 6), 1);
	board = malloc(size * sizeof(int *));
	if (!board)
		return (ft_free_all(NULL, 0, arr), write(1, "Error\n", 6), 1);
	if (!ft_initialize(board, arr, size, i))
		return (write(1, "Error\n", 6), 1);
	if (!ft_solver(board, size))
		return (ft_free_all(board, size, arr), write(1, "Error\n", 6), 1);
	ft_free_all(board, size, arr);
	return (0);
}
