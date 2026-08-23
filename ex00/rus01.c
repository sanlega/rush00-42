/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerodrig <cerodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 12:06:16 by cerodrig          #+#    #+#             */
/*   Updated: 2026/08/23 22:28:44 by cerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	check_row_left(int **board, int size, int row)
{
	int	i;
	int	max;
	int	count;

	i = 1;
	max = 0;
	count = 0;
	while (i < size - 1)
	{
		if (board[row][i] > max)
		{
			count++;
			max = board[row][i];
		}
		i++;
	}
	return (board[row][0] == count);
}

int	check_row_right(int **board, int size, int row)
{
	int	i;
	int	max;
	int	count;

	i = size - 2;
	max = 0;
	count = 0;
	while (i > 0)
	{
		if (board[row][i] > max)
		{
			count++;
			max = board[row][i];
		}
		i--;
	}
	return (board[row][size - 1] == count);
}

int	check_col_top(int **board, int size, int col)
{
	int	i;
	int	max;
	int	count;

	i = 1;
	max = 0;
	count = 0;
	while (i < size - 1)
	{
		if (board[i][col] > max)
		{
			count++;
			max = board[i][col];
		}
		i++;
	}
	return (board[0][col] == count);
}

int	check_col_bottom(int **board, int size, int col)
{
	int	i;
	int	max;
	int	count;

	i = size - 2;
	max = 0;
	count = 0;
	while (i > 0)
	{
		if (board[i][col] > max)
		{
			count++;
			max = board[i][col];
		}
		i--;
	}
	return (board[size - 1][col] == count);
}

int	ft_is_safe(int **board, int size, int row, int col, int num)
{
	int	i;
	int	max_h;

	max_h = size - 2;
	if (num > max_h - board[row][0] + col)
		return (0);
	if (num > max_h - board[row][size - 1] + ((size - 1) - col))
		return (0);
	if (num > max_h - board[0][col] + row)
		return (0);
	if (num > max_h - board[size - 1][col] + ((size - 1) - row))
		return (0);
	i = 1;
	while (i < size - 1)
	{
		if (board[row][i] == num || board[i][col] == num)
			return (0);
		i++;
	}
	return (1);
}

void	ft_pre_fill(int **board, int size)
{
	int	i;
	int	max_h;
	int	j;

	i = 1;
	max_h = size - 2;
	while (i < size - 1)
	{
		if (board[0][i] == 1)
			board[1][i] = max_h;
		if (board[size - 1][i] == 1)
			board[size - 2][i] = max_h;
		if (board[i][0] == 1)
			board[i][1] = max_h;
		if (board[i][size - 1] == 1)
			board[i][size - 2] = max_h;
		if (board[0][i] == 1 && board[size - 1][i] == 2)
			board[size - 2][i] = max_h - 1;
		if (board[size - 1][i] == 1 && board[0][i] == 2)
			board[1][i] = max_h - 1;
		if (board[i][0] == 1 && board[i][size - 1] == 2)
			board[i][size - 2] = max_h - 1;
		if (board[i][size - 1] == 1 && board[i][0] == 2)
			board[i][1] = max_h - 1;
		if (board[0][i] + board[size - 1][i] == max_h + 1)
			board[board[0][i]][i] = max_h;
		if (board[i][0] + board[i][size - 1] == max_h + 1)
			board[i][board[i][0]] = max_h;
		if (board[0][i] == max_h)
		{
			j = 1;
			while (j <= max_h)
			{
				board[j][i] = j;
				j++;
			}
		}
		if (board[size - 1][i] == max_h)
		{
			j = 1;
			while (j <= max_h)
			{
				board[size - 1 - j][i] = j;
				j++;
			}
		}
		if (board[i][0] == max_h)
		{
			j = 1;
			while (j <= max_h)
			{
				board[i][j] = j;
				j++;
			}
		}
		if (board[i][size - 1] == max_h)
		{
			j = 1;
			while (j <= max_h)
			{
				board[i][size - 1 - j] = j;
				j++;
			}
		}
		i++;
	}
}

int	ft_solve(int **board, int size, int row, int col)
{
	int	num;
	int	i;

	if (row == size - 1)
	{
		i = 1;
		while (i < size - 1)
		{
			if (!check_col_top(board, size, i)
				|| !check_col_bottom(board, size, i))
				return (0);
			i++;
		}
		return (1);
	}
	if (col == size - 1)
	{
		if (!check_row_left(board, size, row)
			|| !check_row_right(board, size, row))
			return (0);
		return (ft_solve(board, size, row + 1, 1));
	}
	if (board[row][col] != 0)
		return (ft_solve(board, size, row, col + 1));
	num = 1;
	while (num <= size - 2)
	{
		if (ft_is_safe(board, size, row, col, num))
		{
			board[row][col] = num;
			if (ft_solve(board, size, row, col + 1) == 1)
				return (1);
			board[row][col] = 0;
		}
		num++;
	}
	return (0);
}

int	ft_start_solver(int **board, int size)
{
	ft_pre_fill(board, size);
	return (ft_solve(board, size, 1, 1));
}
