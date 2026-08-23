/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerodrig <cerodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:45:00 by cerodrig          #+#    #+#             */
/*   Updated: 2026/08/23 16:50:00 by cerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Solver completo: opuestos -> logica -> backtracking -> imprimir.
** Solo usamos write() para la salida, como pide el subject.
*/

#include <unistd.h>

int	ft_check_opposites(int **board, int size);
int	ft_apply_logic(int **board, int size);
int	ft_is_safe(int **board, int size, int pos, int val);
int	ft_check_constraints(int **board, int size, int row, int col);

/* Cuenta cuantos valores 1..n encajan en pos sin repetir fila/columna */
static int	ft_count_candidates(int **board, int size, int pos)
{
	int	n;
	int	val;
	int	cnt;

	n = size - 2;
	val = 1;
	cnt = 0;
	while (val <= n)
	{
		if (ft_is_safe(board, size, pos, val))
			cnt++;
		val++;
	}
	return (cnt);
}

/*
** MRV: elige la celda vacia con menos candidatos legales.
** Si alguna vacia tiene 0 candidatos, la rama es imposible.
*/
static int	ft_find_mrv(int **board, int size, int *row, int *col)
{
	int	n;
	int	r;
	int	c;
	int	best;
	int	cnt;
	int	br;
	int	bc;

	n = size - 2;
	best = n + 1;
	br = 0;
	bc = 0;
	r = 1;
	while (r <= n)
	{
		c = 1;
		while (c <= n)
		{
			if (board[r][c] == 0)
			{
				cnt = ft_count_candidates(board, size, r * 16 + c);
				if (cnt < best)
				{
					best = cnt;
					br = r;
					bc = c;
				}
			}
			c++;
		}
		r++;
	}
	if (best > n)
		return (0);
	*row = br;
	*col = bc;
	return (1);
}

/* Imprime la cuadricula interior: "1 2 3 4\n" por fila */
static void	ft_print_solution(int **board, int size)
{
	int	n;
	int	r;
	int	c;
	char	ch;

	n = size - 2;
	r = 1;
	while (r <= n)
	{
		c = 1;
		while (c <= n)
		{
			ch = board[r][c] + '0';
			write(1, &ch, 1);
			if (c < n)
				write(1, " ", 1);
			c++;
		}
		write(1, "\n", 1);
		r++;
	}
}

/*
** Backtracking clasico: prueba 1..n en la celda vacia, valida y recursa.
** Si no hay vacias, el puzzle esta resuelto.
*/
int	ft_backtrack(int **board, int size)
{
	int	row;
	int	col;
	int	val;
	int	n;

	n = size - 2;
	if (!ft_find_mrv(board, size, &row, &col))
		return (1);
	val = 1;
	while (val <= n)
	{
		if (ft_is_safe(board, size, row * 16 + col, val))
		{
			board[row][col] = val;
			if (ft_check_constraints(board, size, row, col)
				&& ft_backtrack(board, size))
				return (1);
			board[row][col] = 0;
		}
		val++;
	}
	return (0);
}

/*
** Orquesta todo el proceso de resolucion.
** Devuelve 0 si el puzzle es invalido o no tiene solucion.
*/
int	ft_solver(int **board, int size)
{
	if (!ft_check_opposites(board, size))
		return (0);
	if (!ft_apply_logic(board, size))
		return (0);
	if (!ft_backtrack(board, size))
		return (0);
	ft_print_solution(board, size);
	return (1);
}
