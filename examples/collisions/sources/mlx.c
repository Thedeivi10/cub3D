/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:51:54 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/22 04:05:27 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <MLX42/MLX42.h>

void	mlx(t_game *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", false);
	if (!game->mlx)
		return ;
	mlx_loop_hook(game->mlx, draw_hook, (void *)game);
	mlx_loop_hook(game->mlx, key_hook, (void *)game);
	mlx_loop(game->mlx);
	if (game->buffer)
		mlx_delete_image(game->mlx, game->buffer);
	mlx_terminate(game->mlx);
}
