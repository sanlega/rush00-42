/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerodrig <cerodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:45:00 by cerodrig          #+#    #+#             */
/*   Updated: 2026/08/23 16:50:00 by cerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_wordc(char *str, char *set);
int	ft_strlen(char *str);

static int	ft_isspace(char c)
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

static int	ft_check_lenght(char *str)
{
	int	words;
	int	n;

	words = ft_wordc(str, " ");
	if (words % 4 != 0)
		return (0);
	n = words / 4;
	if (n < 4 || n > 9)
		return (0);
	return (1);
}

int	ft_check(char **arr, int size, char *orig)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = size - 2;
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
			if ((arr[i][j] - '0') > n || (arr[i][j] - '0') < 1)
				return (0);
			j++;
		}
		i++;
	}
	if (i != n * 4)
		return (0);
	return (1);
}
