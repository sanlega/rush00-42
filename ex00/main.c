/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerodrig <cerodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:44:41 by cerodrig          #+#    #+#             */
/*   Updated: 2026/08/23 16:45:00 by cerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Punto de entrada del rush01.
** Recibe las pistas por argv, monta el tablero y llama al solver.
** Si algo falla imprime "Error\n" y sale con 1.
*/

#include <stdlib.h>
#include <unistd.h>

char	**ft_split(char *str, char *charset);
int		ft_wordc(char *str, char *set);
int		ft_check(char **arr, int size, char *orig);
int		*ft_conform(char **nb, int size, int row);
void	ft_free_all(int **board, int rows, char **arr);
int		ft_solver(int **board, int size);

/*
** Flujo: validar args -> split -> check -> crear board -> solver -> free.
** size = n + 2 porque el board lleva un borde de pistas alrededor del nxn.
*/
int	main(int ac, char **av)
{
	int		i;
	int		**board;
	int		size;
	char	**arr;

	i = 0;
	if (ac != 2)
		return (write(1, "Error\n", 6), 1);
	size = (ft_wordc(av[1], " ")) / 4 + 2;
	arr = ft_split(av[1], " ");
	if (!arr || !ft_check(arr, size, av[1]))
	{
		ft_free_all(NULL, 0, arr);
		return (write(1, "Error\n", 6), 1);
	}
	board = malloc(size * sizeof(int *));
	if (!board)
	{
		ft_free_all(NULL, 0, arr);
		return (write(1, "Error\n", 6), 1);
	}
	while (i < size)
	{
		board[i] = ft_conform(arr, size, i);
		if (!board[i])
		{
			ft_free_all(board, i, arr);
			return (write(1, "Error\n", 6), 1);
		}
		i++;
	}
	if (!ft_solver(board, size))
	{
		ft_free_all(board, size, arr);
		return (write(1, "Error\n", 6), 1);
	}
	ft_free_all(board, size, arr);
	return (0);
}
