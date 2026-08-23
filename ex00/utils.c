/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salegari <salegari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 23:14:17 by salegari          #+#    #+#             */
/*   Updated: 2026/08/23 16:45:00 by cerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Funciones auxiliares compartidas: strlen, free de todo, y escribir celdas.
*/

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
** Libera board (filas parcial o total + punteros) y el split de strings.
** rows = cuantas filas del board ya se habian reservado (util si falla a medias).
*/
void	ft_free_all(int **board, int rows, char **arr)
{
	int	i;

	if (board)
	{
		i = 0;
		while (i < rows)
		{
			free(board[i]);
			i++;
		}
		free(board);
	}
	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

/*
** Escribe val en una celda interior del board.
** pos = row * 16 + col (truco para no pasar mas de 4 parametros).
** Devuelve 0 si hay conflicto con un valor distinto ya puesto.
*/
int	ft_set_cell(int **board, int size, int pos, int val)
{
	int	row;
	int	col;

	row = pos / 16;
	col = pos % 16;
	if (row <= 0 || row >= size - 1 || col <= 0 || col >= size - 1)
		return (0);
	if (board[row][col] == 0)
		board[row][col] = val;
	else if (board[row][col] != val)
		return (0);
	return (1);
}
