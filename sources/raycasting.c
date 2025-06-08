/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:38:15 by davigome          #+#    #+#             */
/*   Updated: 2025/06/08 09:12:40 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_ray(t_map *game, t_ray *ray, int x)
{
	ray->hit = 0;
	ray->camerax = 2 * x / WIDTH - 1;
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
		if (game->grid[ray->mapx][ray->mapy] > 0)
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
}

void	calculate_projection(t_map *game, t_ray	*ray)
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
		calculate_projection(game, &ray);
		draw_wall_slice(game, &ray, x);
	}
}