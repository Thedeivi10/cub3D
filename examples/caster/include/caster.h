/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:15:04 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/20 19:34:54 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <MLX42/MLX42.h>

# define WIDTH 512
# define HEIGHT 512
# define GRID_SIZE 48

typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct s_game
{
	t_point		start;
	t_point		end;
	mlx_t		*mlx;
	mlx_image_t	*buffer;
}				t_game;

void			draw_grid(t_game *game);
void			draw_point(t_game *game, t_point *point, int color);
void			init_ray_scale(t_point *scale, t_point *start, t_point *end);
void			next_intersection(t_point *scale, t_point *start, t_point *end);

#endif