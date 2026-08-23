/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerodrig <cerodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:45:00 by cerodrig          #+#    #+#             */
/*   Updated: 2026/08/23 16:50:00 by cerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_set_cell(int **board, int size, int pos, int val);

static int	ft_fill_n(int **board, int size, int idx, int side)
{
	int	n;
	int	i;

	n = size - 2;
	i = 1;
	while (i <= n)
	{
		if (side == 0 && !ft_set_cell(board, size, i * 16 + idx, i))
			return (0);
		if (side == 1 && !ft_set_cell(board, size, (n - i + 1) * 16 + idx, i))
			return (0);
		if (side == 2 && !ft_set_cell(board, size, idx * 16 + i, i))
			return (0);
		if (side == 3 && !ft_set_cell(board, size, idx * 16 + n - i + 1, i))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_fill_one(int **board, int size, int idx, int side)
{
	int	n;

	n = size - 2;
	if (side == 0)
		return (ft_set_cell(board, size, 1 * 16 + idx, n));
	if (side == 1)
		return (ft_set_cell(board, size, n * 16 + idx, n));
	if (side == 2)
		return (ft_set_cell(board, size, idx * 16 + 1, n));
	return (ft_set_cell(board, size, idx * 16 + n, n));
}

static int	ft_fill_side(int **board, int size, int idx, int side)
{
	int	clue;

	clue = 0;
	if (side == 0)
		clue = board[0][idx];
	if (side == 1)
		clue = board[size - 1][idx];
	if (side == 2)
		clue = board[idx][0];
	if (side == 3)
		clue = board[idx][size - 1];
	if (clue == size - 2)
		return (ft_fill_n(board, size, idx, side));
	if (clue == 1)
		return (ft_fill_one(board, size, idx, side));
	return (1);
}

static int	ft_fill_extra(int **board, int size, int idx)
{
	int	n;

	n = size - 2;
	if (board[0][idx] == 1 && board[size - 1][idx] == 2)
		if (!ft_set_cell(board, size, n * 16 + idx, n - 1))
			return (0);
	if (board[size - 1][idx] == 1 && board[0][idx] == 2)
		if (!ft_set_cell(board, size, 1 * 16 + idx, n - 1))
			return (0);
	if (board[idx][0] == 1 && board[idx][size - 1] == 2)
		if (!ft_set_cell(board, size, idx * 16 + n, n - 1))
			return (0);
	if (board[idx][size - 1] == 1 && board[idx][0] == 2)
		if (!ft_set_cell(board, size, idx * 16 + 1, n - 1))
			return (0);
	if (board[0][idx] + board[size - 1][idx] == n + 1)
		if (!ft_set_cell(board, size, board[0][idx] * 16 + idx, n))
			return (0);
	if (board[idx][0] + board[idx][size - 1] == n + 1)
		if (!ft_set_cell(board, size, idx * 16 + board[idx][0], n))
			return (0);
	return (1);
}

int	ft_apply_logic(int **board, int size)
{
	int	n;
	int	i;

	n = size - 2;
	i = 1;
	while (i <= n)
	{
		if (!ft_fill_side(board, size, i, 0)
			|| !ft_fill_side(board, size, i, 1)
			|| !ft_fill_side(board, size, i, 2)
			|| !ft_fill_side(board, size, i, 3)
			|| !ft_fill_extra(board, size, i))
			return (0);
		i++;
	}
	return (1);
}
