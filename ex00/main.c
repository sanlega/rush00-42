/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerodrig <cerodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:44:41 by cerodrig          #+#    #+#             */
/*   Updated: 2026/08/22 21:46:07 by salegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//void	convert_str_to_int(char *str);
void	rush(char *str);
char	**ft_split(char *str, char *charset);
int	ft_wordc(char *str, char *set);

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r'
		|| c == '\f' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	s;

	i = 0;
	res = 0;
	s = 1;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * s);
}

void	ft_free(int **board, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(board[i]);
		i++;
	}
}

int	*ft_conform(char **nb, int size, int row)
{
	int	i;
	int	*table;

	i = 0;
	table = malloc(size * sizeof(int));
	if (!table)
		return (NULL);
	while (i < size)
		table[i++] = 0;
	if (row == 0)
	{
		i = 1;
		while (i < size - 1)
		{
			table[i] = ft_atoi(nb[i]);
			i++;
		}
	}
	else if (row == size - 1)
	{
		i = 1;
		while (i < size - 1)
		{
			table[i] = ft_atoi(nb[i + 4]);
			i++;
		}
	}
	else
	{
		table[0] = ft_atoi(nb[row + 8]);
		table[size - 1] = ft_atoi(nb[row + 12]);
	}
	return (table);
}

int	main(int ac, char **av)
{
	int	i;
	int	**board;
	int	 size;
	char **arr;

	i = 0;
	size = (ft_wordc(av[1], " ")) / 4 + 2;
	arr = ft_split(av[1], " ");
	if (ac != 2)
		return (write(1, "Error\n", 6), 0);
	board = malloc(size * sizeof(int *));
	if (!board)
		return (write(1, "Error\n", 6), 0);
	while (i < size)
	{
		board[i] = ft_conform(arr++, size, i);
		if (!board[i])
		{
			ft_free(board, i);
			free(board);
			return (write(1, "Error\n", 6), 0);
		}
		i++;
	}

	int y;
	int x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			printf("%d ", board[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
	// ft_rush(board, size);
	return (0);
}
