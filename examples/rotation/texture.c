/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 04:54:10 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/23 02:54:54 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_.h"
#include <MLX42/MLX42.h>

void	delete_textures(t_game *game)
{
	if (game->scene.north_texture)
	{
		mlx_delete_texture(game->scene.north_texture);
		game->scene.north_texture = 0;
	}
	if (game->scene.south_texture)
	{
		mlx_delete_texture(game->scene.south_texture);
		game->scene.south_texture = 0;
	}
	if (game->scene.east_texture)
	{
		mlx_delete_texture(game->scene.east_texture);
		game->scene.east_texture = 0;
	}
	if (game->scene.west_texture)
	{
		mlx_delete_texture(game->scene.west_texture);
		game->scene.west_texture = 0;
	}
}

int	load_textures(t_game *game)
{
	game->scene.north_texture = mlx_load_png(game->scene.north_tex);
	if (!game->scene.north_texture)
		return (KO);
	game->scene.south_texture = mlx_load_png(game->scene.south_tex);
	if (!game->scene.south_texture)
		return (KO);
	game->scene.east_texture = mlx_load_png(game->scene.east_tex);
	if (!game->scene.east_texture)
		return (KO);
	game->scene.west_texture = mlx_load_png(game->scene.west_tex);
	if (!game->scene.west_texture)
		return (KO);
	return (OK);
}

mlx_texture_t	*get_texture_from_direction(t_game *game, t_point *direction)
{
	if (direction->y < 0)
		return (game->scene.north_texture);
	if (direction->y > 0)
		return (game->scene.south_texture);
	if (direction->x < 0)
		return (game->scene.west_texture);
	return (game->scene.east_texture);
}

uint32_t	get_texture_pixel(mlx_texture_t *texture, t_point *image,
		t_point *direction)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	p;
	uint32_t	pixel;

	if (direction->x < 0 || direction->y > 0)
		x = texture->width * (1.0 - image->x);
	else
		x = texture->width * image->x;
	if (x >= texture->width)
		x = 0;
	y = texture->height * image->y;
	if (y >= texture->height)
		y = 0;
	p = *(uint32_t *)&texture->pixels[(y * texture->width + x) * 4];
	pixel = 0;
	pixel += (p & 0x000000ff) << 24;
	pixel += (p & 0x0000ff00) << 8;
	pixel += (p & 0x00ff0000) >> 8;
	pixel += 0x000000ff;
	return (pixel);
}
