/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:36:24 by davigome          #+#    #+#             */
/*   Updated: 2025/06/08 09:26:21 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*game;

	game = (t_map *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_W)
		game->input.w = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_S)
		game->input.s = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_A)
		game->input.a = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_D)
		game->input.d = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_LEFT)
		game->input.left = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_RIGHT)
		game->input.right = (keydata.action != MLX_RELEASE);
}

void	ft_init_mlx(t_map	*game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!game->mlx)
	{
		fprintf(stderr, "Error:\nCould not init MLX42");
		ft_bad_close(game);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		fprintf(stderr, "Error:\nCould not create image");
		ft_bad_close(game);
	}
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_loop_hook(game->mlx, &update_game, game);
	mlx_key_hook(game->mlx, &key_hook, game);
}

void	ft_run(t_map *game)
{
	ft_init_mlx(game);
	ft_load_textures(game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
