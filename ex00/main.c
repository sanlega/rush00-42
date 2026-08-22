/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerodrig <cerodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:44:41 by cerodrig          #+#    #+#             */
/*   Updated: 2026/08/22 17:44:26 by cerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

//void	convert_str_to_int(char *str);
void	rush(char *str);

int	main(int argc, char *argv[])
{
	if (argc < 2)
	{
		write(1, "Pasa la cadena, bro!", 20);
		return (1);
	}
	rush(argv[1]);
	//convert_str_to_int(argv[1]);
	return (1);
}
