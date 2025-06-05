/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:38:15 by davigome          #+#    #+#             */
/*   Updated: 2025/06/05 17:57:52 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	raycast_all_columns(t_map *game)
{
	int		x;
	t_ray	ray;

	x = -1;
	while (++x < WIDTH)
	{
		init_ray(game, &ray);
		calculate_steps_and_sidedist(game, &ray);
		perform_dda(game, &ray);
		calculate_projection(game, &ray);
		draw_wall_slice(game, &ray, x);
	}
}