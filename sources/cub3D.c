/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:21:35 by davigome          #+#    #+#             */
/*   Updated: 2025/05/30 19:32:23 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_check_name(char **argv)
{
	int len;

	len = ft_strlen(argv[1]);
	if (argv[1][len - 1] != 'b' ||  argv[1][len - 2] != 'u'
		|| argv[1][len - 3] != 'c' || argv[1][len - 2] != '.')
	{
		fprintf(stderr, "Error\nThe map must end with .cub");
		exit(1);
	}
}

void	ft_checks(t_map *game, char **argv)
{
	ft_check_name(argv);
}

int main(int argc, char **argv)
{
	t_map *game;
	
	game = NULL;
	if (argc != 2)
		fprintf(stderr, "Error\ncub3D needs a .cub map.\n");
	ft_checks(game, argv);
	return (EXIT_SUCCESS);
}