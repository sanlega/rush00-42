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

static void	ft_write_char(char c)
{
	write(1, &c, 1);
}

/* Busca la primera celda interior vacia (valor 0) de arriba a abajo */
static int	ft_find_empty(int **board, int size, int *row, int *col)
{
	int	n;
	int	r;
	int	c;

	n = size - 2;
	r = 1;
	while (r <= n)
	{
		c = 1;
		while (c <= n)
		{
			if (board[r][c] == 0)
			{
				*row = r;
				*col = c;
				return (1);
			}
			c++;
		}
		r++;
	}
	return (0);
}

/* Imprime la cuadricula interior: "1 2 3 4\n" por fila */
static void	ft_print_solution(int **board, int size)
{
	int	n;
	int	r;
	int	c;

	n = size - 2;
	r = 1;
	while (r <= n)
	{
		c = 1;
		while (c <= n)
		{
			ft_write_char(board[r][c] + '0');
			if (c < n)
				ft_write_char(' ');
			c++;
		}
		ft_write_char('\n');
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
	if (!ft_find_empty(board, size, &row, &col))
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
