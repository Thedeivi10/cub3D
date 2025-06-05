/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:25:16 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/21 19:01:37 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "caster.h"

void	map_mock(t_game *game)
{
	static char	*map[7] = {
		"1111111",
		"1100001",
		"1000111",
		"1000001",
		"1000001",
		"1110001",
		"1111111"};

	game->s_map = map;
	game->width = 7;
	game->height = 7;
	game->scene.ceiling_color = 0xcaf0f8ff;
	game->scene.floor_color = 0x81b29a;
}
