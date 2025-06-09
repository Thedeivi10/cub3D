/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:38:15 by davigome          #+#    #+#             */
/*   Updated: 2025/06/09 12:45:23 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_ray(t_map *game, t_ray *ray, int x)
{
	ray->hit = 0;
	ray->camerax = 2.0 * x / (double)WIDTH - 1.0;
	ray->raydirx = game->player.dir_x + game->player.plane_x * ray->camerax;
	ray->raydiry = game->player.dir_y + game->player.plane_y * ray->camerax;
	ray->mapx = (int)game->player.x;
	ray->mapy = (int)game->player.y;
	if (ray->raydirx == 0)
    	ray->deltadistx = 1e30;
	else 
    	ray->deltadistx = 1 / ray->raydirx;
	if (ray->deltadistx < 0)
		ray->deltadistx = -ray->deltadistx;
	if (ray->raydiry == 0)
		ray->deltadisty = 1e30;
	else 
    	ray->deltadisty = 1 / ray->raydiry;
    if (ray->deltadisty < 0)
        ray->deltadisty = -ray->deltadisty;
}

void	calculate_steps_and_sidedist(t_map *game, t_ray *ray)
{
	if (ray->raydirx < 0 )
	{
		ray->stepx = -1;
		ray->sidedistx = (game->player.x - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1 - game->player.x) * ray->deltadistx;
	}
	if (ray->raydiry < 0 )
	{
		ray->stepy = -1;
		ray->sidedisty = (game->player.y - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1 - game->player.y) * ray->deltadisty;
	}
}

void	perform_dda(t_map *game, t_ray *ray)
{
	while(ray->hit == 0)
	{
		if(ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (game->grid[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
}

void	calculate_projection(t_ray	*ray)
{
	int	lineheight;
	int	drawstart;
	int	drawend;

	lineheight = (int)(HEIGHT / ray->perpwalldist);
	drawstart = -lineheight / 2 + HEIGHT / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = lineheight / 2 + HEIGHT / 2;
	if (drawend >= HEIGHT)
		drawend = HEIGHT - 1;
	ray->drawstart = drawstart;
	ray->drawend = drawend;
	ray->lineheight = lineheight;
}

uint32_t	get_pixel_from_texture(mlx_image_t *img, int x, int y)
{
	if (!img || x < 0 || y < 0 || x >= (int)img->width || y >= (int)img->height)
		return (0);
	int i = (y * img->width + x) * 4;
	return (
		(img->pixels[i] << 24) |
		(img->pixels[i + 1] << 16) |
		(img->pixels[i + 2] << 8) |
		(img->pixels[i + 3])
	);
}

void	draw_wall_slice(t_map *game, t_ray *ray, int x)
{
	mlx_image_t *texture;

	if (ray->side == 0)
		texture = (ray->raydirx > 0) ? game->images.ea : game->images.we;
	else
		texture = (ray->raydiry > 0) ? game->images.so : game->images.no;

	// Cálculo de wall_x
	double wall_x;
	if (ray->side == 0)
		wall_x = game->player.y + ray->perpwalldist * ray->raydiry;
	else
		wall_x = game->player.x + ray->perpwalldist * ray->raydirx;
	wall_x -= floor(wall_x);

	int tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->raydirx > 0) || (ray->side == 1 && ray->raydiry < 0))
		tex_x = texture->width - tex_x - 1;

	// Escalar y dibujar
	for (int y = ray->drawstart; y < ray->drawend; y++)
	{
		int d = y * 256 - HEIGHT * 128 + ray->lineheight * 128;
		int tex_y = (d * texture->height) / ray->lineheight / 256;
		uint32_t color = get_pixel_from_texture(texture, tex_x, tex_y);
		mlx_put_pixel(game->img, x, y, color);
	}
}

/* void	draw_wall_slice(t_map *game, t_ray *ray, int x)
{
	mlx_image_t *texture;
	t_line line;

	if (ray->side == 0)
	{
		if (ray->raydirx > 0)
			texture = game->images.ea;
		else
			texture = game->images.we;
	}
	else
	{
		if (ray->raydiry > 0)
			texture = game->images.so;
		else
			texture = game->images.no;
	}
	uint32_t color = 0xFFFFFFFF;
	if (texture == game->images.no)
		color = 0xFF0000FF; //Rojo
	else if (texture == game->images.so)
		color = 0x00FF00FF; //verde
	else if (texture == game->images.ea)
		color = 0x0000FFFF; // azul
	else if (texture == game->images.we)
		color = 0xFFFF00FF; // amarillo
	line.x = x;
	line.y_start = ray->drawstart;
	line.y_end = ray->drawend;
	line.color = color;

	draw_vertical_line(game->img, line);
} */


void	raycast_all_columns(t_map *game)
{
	int		x;
	t_ray	ray;

	x = -1;
	while (++x < WIDTH)
	{
		init_ray(game, &ray, x);
		calculate_steps_and_sidedist(game, &ray);
		perform_dda(game, &ray);
		calculate_projection(&ray);
		draw_wall_slice(game, &ray, x);
	}
}