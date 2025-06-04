/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:16:51 by jotrujil          #+#    #+#             */
/*   Updated: 2025/06/04 14:33:18 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_background(t_map *game)
{
	uint32_t	c_color;
	uint32_t	f_color;
	int			x;
	int			y;

	c_color = (game->ceiling_r << 24) | (game->ceiling_g << 16)
		| (game->ceiling_b << 8) | 255;
	f_color = (game->floor_r << 24) | (game->floor_g << 16)
		| (game->floor_b << 8) | 255;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, c_color);
			else
				mlx_put_pixel(game->img, x, y, f_color);
			x++;
		}
		y++;
	}
}

void	update_game(void *param)
{
	t_map	*game;

	game = (t_map *)param;
	handle_input(game);
	draw_background(game);
}
