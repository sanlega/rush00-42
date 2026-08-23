/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerodrig <cerodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:50:00 by cerodrig          #+#    #+#             */
/*   Updated: 2026/08/23 16:50:00 by cerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_atoi(char *str);

static void	ft_fill_top(int *table, char **nb, int size)
{
	int	i;

	i = 1;
	while (i < size - 1)
	{
		table[i] = ft_atoi(nb[i - 1]);
		i++;
	}
}

static void	ft_fill_bottom(int *table, char **nb, int size, int n)
{
	int	i;

	i = 1;
	while (i < size - 1)
	{
		table[i] = ft_atoi(nb[i + n - 1]);
		i++;
	}
}

static void	ft_fill_sides(int *table, char **nb, int size, int row)
{
	int	n;

	n = size - 2;
	table[0] = ft_atoi(nb[2 * n + row - 1]);
	table[size - 1] = ft_atoi(nb[3 * n + row - 1]);
}

int	*ft_conform(char **nb, int size, int row)
{
	int	i;
	int	n;
	int	*table;

	n = size - 2;
	i = 0;
	table = malloc(size * sizeof(int));
	if (!table)
		return (NULL);
	while (i < size)
		table[i++] = 0;
	if (row == 0)
		ft_fill_top(table, nb, size);
	else if (row == size - 1)
		ft_fill_bottom(table, nb, size, n);
	else
		ft_fill_sides(table, nb, size, row);
	return (table);
}
