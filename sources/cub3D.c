/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:21:35 by davigome          #+#    #+#             */
/*   Updated: 2025/06/02 21:01:47 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_map	*game;

	if (argc == 2)
	{
		game = malloc(sizeof(t_map));
		ft_checks(game, argv);
		ft_free_map(game);
	}
	else
	{
		fprintf(stderr, "Error\ncub3D needs a .cub map.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
