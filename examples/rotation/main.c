/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 04:22:46 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/23 03:33:18 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_.h"
#include <math.h>

int	main(void)
{
	t_game	game;

	game.debug_mode = 0;
	map_mock(&game);
	mlx(&game);
	end_mlx(&game);
	return (0);
}
