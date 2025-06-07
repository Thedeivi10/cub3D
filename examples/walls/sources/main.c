/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 04:22:46 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/21 17:54:30 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "caster.h"
#include <math.h>

static void	draw_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return ;
	draw_scene(game);
	draw_minimap(game);
	mlx_image_to_window(game->mlx, game->scene_buffer, 0, 0);
	//mlx_image_to_window(game->mlx, game->minimap_buffer, 0, 0);
}

static void	key_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->start.y -= 0.1f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->start.y += 0.1f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->start.x -= 0.1f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->start.x += 0.1f;
}

static void	cursor_hook(double x_pos, double y_pos, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->end.x = x_pos / GRID_SIZE;
	game->end.y = y_pos / GRID_SIZE;
}

int	main(void)
{
	t_game	game;

	map_mock(&game);
	game.render_columns = game.height * 1.5 * GRID_SIZE;
	game.mlx = mlx_init(game.width * GRID_SIZE + game.render_columns, game.height * GRID_SIZE,
			"walls", false);
	if (!game.mlx)
		return (1);
	game.minimap_buffer = (mlx_image_t *)0;
	game.start.y = (double)game.height * GRID_SIZE / (2 * GRID_SIZE);
	game.start.x = (double)game.width * GRID_SIZE / (2 * GRID_SIZE);
	game.end.y = 1.0f;
	game.end.x = 1.0f;
	mlx_loop_hook(game.mlx, draw_hook, (void *)&game);
	mlx_loop_hook(game.mlx, key_hook, (void *)&game);
	mlx_cursor_hook(game.mlx, cursor_hook, &game);
	mlx_loop(game.mlx);
	if (game.minimap_buffer)
		mlx_delete_image(game.mlx, game.minimap_buffer);
	mlx_terminate(game.mlx);
	return (0);
}
