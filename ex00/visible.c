/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visible.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerodrig <cerodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:50:00 by cerodrig          #+#    #+#             */
/*   Updated: 2026/08/23 16:50:00 by cerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_count_top(int **board, int size, int idx)
{
	int	max;
	int	cnt;
	int	n;
	int	p;

	max = 0;
	cnt = 0;
	n = size - 2;
	p = 1;
	while (p <= n)
	{
		if (board[p][idx] > max)
		{
			max = board[p][idx];
			cnt++;
		}
		p++;
	}
	return (cnt);
}

static int	ft_count_bottom(int **board, int size, int idx)
{
	int	max;
	int	cnt;
	int	p;

	max = 0;
	cnt = 0;
	p = size - 2;
	while (p >= 1)
	{
		if (board[p][idx] > max)
		{
			max = board[p][idx];
			cnt++;
		}
		p--;
	}
	return (cnt);
}

static int	ft_count_left(int **board, int size, int idx)
{
	int	max;
	int	cnt;
	int	n;
	int	p;

	max = 0;
	cnt = 0;
	n = size - 2;
	p = 1;
	while (p <= n)
	{
		if (board[idx][p] > max)
		{
			max = board[idx][p];
			cnt++;
		}
		p++;
	}
	return (cnt);
}

static int	ft_count_right(int **board, int size, int idx)
{
	int	max;
	int	cnt;
	int	p;

	max = 0;
	cnt = 0;
	p = size - 2;
	while (p >= 1)
	{
		if (board[idx][p] > max)
		{
			max = board[idx][p];
			cnt++;
		}
		p--;
	}
	return (cnt);
}

int	ft_count_visible(int **board, int size, int idx, int side)
{
	if (side == 0)
		return (ft_count_top(board, size, idx));
	if (side == 1)
		return (ft_count_bottom(board, size, idx));
	if (side == 2)
		return (ft_count_left(board, size, idx));
	return (ft_count_right(board, size, idx));
}
