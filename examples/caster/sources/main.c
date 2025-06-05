/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 04:22:46 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/20 19:34:29 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "caster.h"
#include <math.h>

static void	draw_ray(t_game *game, t_point *start, t_point *end, int color)
{
	t_point	scale;
	t_point	last;

	init_ray_scale(&scale, start, end);
	last.x = start->x;
	last.y = start->y;
	while (fabs(last.x - start->x) < fabs(end->x - start->x))
	{
		draw_point(game, &last, color);
		next_intersection(&scale, &last, end);
	}
}

static void	draw_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return ;
	if (game->buffer)
		mlx_delete_image(game->mlx, game->buffer);
	game->buffer = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->buffer)
		return ;
	draw_grid(game);
	draw_ray(game, &game->start, &game->end, 0xFFFF00FF);
	draw_point(game, &game->start, 0x00FF00AA);
	draw_point(game, &game->end, 0xFF0000AA);
	mlx_image_to_window(game->mlx, game->buffer, 0, 0);
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

	game.mlx = mlx_init(WIDTH, HEIGHT, "caster", false);
	if (!game.mlx)
		return (1);
	game.buffer = (mlx_image_t *)0;
	game.start.y = (double)HEIGHT / (2 * GRID_SIZE);
	game.start.x = (double)WIDTH / (2 * GRID_SIZE);
	game.end.y = 1.0f;
	game.end.x = 1.0f;
	mlx_loop_hook(game.mlx, draw_hook, (void *)&game);
	mlx_loop_hook(game.mlx, key_hook, (void *)&game);
	mlx_cursor_hook(game.mlx, cursor_hook, &game);
	mlx_loop(game.mlx);
	if (game.buffer)
		mlx_delete_image(game.mlx, game.buffer);
	mlx_terminate(game.mlx);
	return (0);
}
