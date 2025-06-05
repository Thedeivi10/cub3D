/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:54:03 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/22 07:23:04 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <MLX42/MLX42.h>

void	draw_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return ;
	if (game->buffer)
		mlx_delete_image(game->mlx, game->buffer);
	game->buffer = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->buffer)
		return ;
	draw_scene(game);
	draw_minimap(game);
	mlx_image_to_window(game->mlx, game->buffer, 0, 0);
}

void	key_hook(void *param)
{
	t_game	*game;
	t_point	direction;
	double	angle;

	direction.x = 0.0;
	direction.y = 0.0;
	angle = 0;
	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx,
			MLX_KEY_UP))
		direction.x = 1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx,
			MLX_KEY_DOWN))
		direction.x = -1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		direction.y = 1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		direction.y = -1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		angle += 0.05;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		angle -= 0.05;
	rotate_view(&game->player, angle);
	move_view(game, &game->player, &direction);
}
