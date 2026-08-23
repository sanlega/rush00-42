/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerodrig <cerodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:45:00 by cerodrig          #+#    #+#             */
/*   Updated: 2026/08/23 16:50:00 by cerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Comprobaciones de validez: opuestos, duplicados y pistas cumplidas.
*/

int	ft_count_visible(int **board, int size, int idx, int side);

/* axis 0 = fila, axis 1 = columna. True si no queda ningun 0 */
static int	ft_line_complete(int **board, int size, int idx, int axis)
{
	int	n;
	int	i;

	n = size - 2;
	i = 1;
	while (i <= n)
	{
		if (axis == 0 && board[idx][i] == 0)
			return (0);
		if (axis == 1 && board[i][idx] == 0)
			return (0);
		i++;
	}
	return (1);
}

/*
** Regla rapida: top + bottom (o left + right) no puede superar n+1.
** Si no se cumple el puzzle es imposible y ni probamos backtracking.
*/
int	ft_check_opposites(int **board, int size)
{
	int	n;
	int	i;

	n = size - 2;
	i = 1;
	while (i <= n)
	{
		if (board[0][i] + board[size - 1][i] > n + 1)
			return (0);
		if (board[i][0] + board[i][size - 1] > n + 1)
			return (0);
		i++;
	}
	return (1);
}

/*
** Comprueba que val no se repita en la fila ni en la columna de pos.
** pos = row * 16 + col
*/
int	ft_is_safe(int **board, int size, int pos, int val)
{
	int	n;
	int	i;
	int	row;
	int	col;

	row = pos / 16;
	col = pos % 16;
	n = size - 2;
	i = 1;
	while (i <= n)
	{
		if (board[row][i] == val && i != col)
			return (0);
		if (board[i][col] == val && i != row)
			return (0);
		i++;
	}
	return (1);
}

/*
** Cuando una fila o columna se completa, compara visibles con las pistas.
** Se llama en cada paso del backtracking para podar ramas malas pronto.
*/
int	ft_check_constraints(int **board, int size, int row, int col)
{
	if (ft_line_complete(board, size, row, 0))
	{
		if (ft_count_visible(board, size, row, 2) != board[row][0])
			return (0);
		if (ft_count_visible(board, size, row, 3) != board[row][size - 1])
			return (0);
	}
	if (ft_line_complete(board, size, col, 1))
	{
		if (ft_count_visible(board, size, col, 0) != board[0][col])
			return (0);
		if (ft_count_visible(board, size, col, 1) != board[size - 1][col])
			return (0);
	}
	return (1);
}
