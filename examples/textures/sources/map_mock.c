/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:25:16 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/22 07:24:30 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	map_mock(t_game *game)
{
	static char	*map[9] = {
		"111111111111111111111",
		"110000000000000000001",
		"110000000000000000001",
		"110000000000000000001",
		"100011110011000000001",
		"100000110011111111101",
		"100000000011000000001",
		"111000000011000000001",
		"111111111111111111111"};

	game->s_map = map;
	game->width = 21;
	game->height = 9;
	game->player.position.y = 3.5;
	game->player.position.x = 4.5;
	game->player.direction.x = 1.0;
	game->player.direction.y = 0.0;
	game->scene.ceiling_color = 0x00b4d8ff;
	game->scene.floor_color = 0xfb8500ff;
	game->scene.north_tex = "./assets/t1.png";
	game->scene.south_tex = "./assets/t2.png";
	game->scene.east_tex = "./assets/t3.png";
	game->scene.west_tex = "./assets/t4.png";
}
