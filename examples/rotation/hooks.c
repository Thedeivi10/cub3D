/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:54:03 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/23 03:42:30 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_.h"
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

void	movement_hook(void *param)
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

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		end_mlx(game);
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		end_mlx(game);
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		game->debug_mode = !game->debug_mode;
}

void	cursor_hook(double x_pos, double y_pos, void *param)
{
	t_game	*game;
	double	angle;

	y_pos = y_pos;
	game = (t_game *)param;
	if (game->last_mouse_x == -1)
		game->last_mouse_x = x_pos;
	angle = game->last_mouse_x - x_pos;
	game->last_mouse_x = x_pos;
	angle *= PLAYER_SPEED / 2;
	rotate_view(&game->player, angle);
}
