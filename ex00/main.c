/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerodrig <cerodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:44:41 by cerodrig          #+#    #+#             */
/*   Updated: 2026/08/23 00:47:49 by salegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//void	convert_str_to_int(char *str);
void	rush(char *str);
char	**ft_split(char *str, char *charset);
int	ft_wordc(char *str, char *set);
int	ft_strlen(char *str);

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

int	ft_check_lenght(char *str)
{
	int	size;

	size = (ft_wordc(str, " ")) / 4;
	if (size < 4 || size > 9)
		return (0);
	return (1);
}

int	ft_check(char **arr, int size, char *orig)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!ft_check_lenght(orig))
		return (0);
	while (arr[i])
	{
		if (ft_strlen(arr[i]) > 1)
			return (0);
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] < '0' || arr[i][j] > '9')
				return (0);
			if ((arr[i][j] - '0') > (size - 2) || (arr[i][j] - '0') < 1)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_free(int **board, int size, char **arr)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(board[i]);
		i++;
	}
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
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
			table[i] = ft_atoi(nb[i - 1]);
			i++;
		}
	}
	else if (row == size - 1)
	{
		i = 1;
		while (i < size - 1)
		{
			table[i] = ft_atoi(nb[i + 3]);
			i++;
		}
	}
	else
	{
		table[0] = ft_atoi(nb[row + 7]);
		table[size - 1] = ft_atoi(nb[row + 11]);
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
	if (ac != 2)
		return (write(1, "Error\n", 6), 1);
	size = (ft_wordc(av[1], " ")) / 4 + 2;
	arr = ft_split(av[1], " ");
	// PROTEGER ESTE MALLOC
	if(!ft_check(arr, size, av[1]))
		return (write(1, "Error\n", 6), 1);
	board = malloc(size * sizeof(int *));
	if (!board)
		return (write(1, "Error\n", 6), 1);
	while (i < size)
	{
		board[i] = ft_conform(arr, size, i);
		if (!board[i])
		{
			ft_free(board, i, arr);
			free(board);
			return (write(1, "Error\n", 6), 1);
		}
		i++;
	}

// IMPRIMIR LA TABLA, PRUEBA:
	int y;
	int x = 1;
	while (x < size )
	{
		y = 1;
		while (y < size )
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
