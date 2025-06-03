/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:36:24 by davigome          #+#    #+#             */
/*   Updated: 2025/06/03 20:51:05 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_init_mlx(t_map	*game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, TITRE, true);
	if (!game->mlx)
	{
		ft_printf("Error:\nCould not init MLX42");
		ft_bad_close(game);
	}
}

void	ft_run(t_map *game)
{
	ft_init_mlx(game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}