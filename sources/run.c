/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:36:24 by davigome          #+#    #+#             */
/*   Updated: 2025/06/04 15:00:13 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_init_mlx(t_map	*game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!game->mlx)
	{
		ft_printf("Error:\nCould not init MLX42");
		ft_bad_close(game);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		ft_printf("Error:\nCould not create image");
		ft_bad_close(game);
	}
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_loop_hook(game->mlx, &update_game, game);
	mlx_key_hook(game->mlx, &key_hook, game);
}

void	ft_run(t_map *game)
{
	ft_init_mlx(game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
