/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:51:54 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/23 03:30:43 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_.h"
#include <MLX42/MLX42.h>
#include <stdlib.h>

void	mlx(t_game *game)
{
	if (load_textures(game) == KO)
		return ;
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", false);
	if (!game->mlx)
		return ;
	mlx_loop_hook(game->mlx, draw_hook, (void *)game);
	mlx_loop_hook(game->mlx, movement_hook, (void *)game);
	mlx_key_hook(game->mlx, key_hook, (void *)game);
	mlx_cursor_hook(game->mlx, cursor_hook, (void *)game);
	mlx_loop(game->mlx);
}

void	end_mlx(t_game *game)
{
	delete_textures(game);
	if (game->buffer)
		mlx_delete_image(game->mlx, game->buffer);
	mlx_terminate(game->mlx);
	exit(0);
}
