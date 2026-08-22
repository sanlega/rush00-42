/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerodrig <cerodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:30:14 by cerodrig          #+#    #+#             */
/*   Updated: 2026/08/22 17:42:58 by cerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	rush(int col_top[4], int col_bottom[4], int	row_left[4], int row_right[4]);

void	convert_str_to_int(char *str)
{
	int	col_top[4];
	int	col_bottom[4];
	int	row_left[4];
	int	row_right[4];
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (str[i] != '\0')
	{
		if (pos == 4)
			pos = 0;
		if (str[i] != ' ')
		{
			if (i == 0 || i == 2 || i == 4 || i == 6)
				col_top[pos] = str[i] - '0';
			if (i == 8 || i == 10 || i == 12 || i == 14)
				col_bottom[pos] = str[i] - '0';
			if (i == 16 || i == 18 || i == 20 || i == 22)
				row_left[pos] = str[i] - '0';
			if (i == 24 || i == 26 || i == 28 || i == 30)
				row_right[pos] = str[i] - '0';
			pos++;
		}
		i++;
	}
	printf("col_top: %i %i %i %i  col_bottom: %i %i %i %i\n\
row_letf: %i %i %i %i  row_right: %i %i %i %i \n",\
		col_top[0], col_top[1], col_top[2], col_top[3],\
		col_bottom[0], col_bottom[1], col_bottom[2], col_bottom[3],\
		row_left[0], row_left[1], row_left[2], row_left[3],\
		row_right[0], row_right[1], row_right[2], row_right[3]);

	rush(col_top, col_bottom, row_left, row_right);
}
void	rush(int col_top[4], int col_bottom[4], int	row_left[4], int row_right[4])
{
	int matriz[4][4];
	int	m_row;
	int m_col;
	int	i;
	int	num;

	num = 1;
	m_row = 0;
	m_col = 0;
	i = 0;
	while (col_top[i] < 4)
	{
		if (col_top[i] == 4)
		{
			while (m_row < 4)
			{
				m_col = i;
				matriz[m_row][m_col] = num;
				m_row++;
				num++;
			}
			num = 1;
			m_row = 0;
			m_col = 0;
		}
		if (col_top[i] == 1)
		{
			m_col = i;
			matriz[m_row][m_col] = 4;
		}
		i++;
	}
	num = 1;
	m_row = 3;
	m_col = 0;
	i = 0;
	while (col_bottom[i] < 4)
	{
		if (col_bottom[i] == 4)
		{
			while (m_row < -1)
			{
				m_col = i;
				matriz[m_row][m_col] = num;
				m_row--;
				num++;
			}
		}
		num = 1;
		m_row = 3;
		if (col_bottom[i] == 1)
		{
			m_col = i;
			matriz[m_row][m_col] = 4;
		}
		i++;
	}
 //==========================================================
	num = 1;
	m_row = 0;
	m_col = 0;
	i = 0;
	while (row_left[i] < 4)
	{
		if (row_left[i] == 4)
		{
			while (m_col < 4)
			{
				m_row = i;
				matriz[m_row][m_col] = num;
				m_col++;
				num++;
			}
			num = 1;
			m_row = 0;
			m_col = 0;
		}
		if (row_left[i] == 1)
		{
			m_row = i;
			matriz[m_row][m_col] = 4;
		}
		i++;
	}
	num = 1;
	m_row = 0;
	m_col = 3;
	i = 0;
	while (row_right[i] < 4)
	{
		if (row_right[i] == 4)
		{
			while (m_col < -1)
			{
				m_row = i;
				matriz[m_row][m_col] = num;
				m_col--;
				num++;
			}
		}
		num = 1;
		m_col = 3;
		if (row_right[i] == 1)
		{
			m_row = i;
			matriz[m_row][m_col] = 4;
		}
		i++;
	}

	m_col = 0;
	m_row = 0;
		while (m_row < 4)
		{
			while (m_col < 4)
			{
				printf("%i ", matriz[m_row][m_col]);
				m_col++;
			}
			printf("%c", '\n');
			m_row++;
			m_col = 0;
		}
}
