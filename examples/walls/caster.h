/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:15:04 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/21 19:32:39 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CASTER_H
# define CASTER_H

# include <MLX42/MLX42.h>

# define GRID_SIZE 90
# define FOV 1

typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct s_ray
{
	t_point		start;
	t_point		end;
	t_point		scale;
}				t_ray;

typedef struct	s_scene
{
	char	*north_tex;
	char	*south_tex;
	char	*east_tex;
	char	*west_tex;
	int		floor_color;
	int		ceiling_color;
}	t_scene;

typedef struct s_game
{
	t_point		start;
	t_point		end;
	int			width;
	int			height;
	int			render_columns;
	char		**s_map;
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*minimap_buffer;
	mlx_image_t	*scene_buffer;
}				t_game;

void			init_ray(t_ray *ray, t_point *start, t_point *end);
void			intersect_ray(t_ray *ray, t_point *intersection,
					t_point *displacement, t_point *dir);
void			collide_ray(t_game *game, t_ray *ray, t_point *collision,
					t_point *direction);

void			draw_minimap(t_game *game);
int				get_direction_color(t_point *direction);

void			draw_scene(t_game *game);

void			draw_grid(t_game *game);
void			draw_point(t_game *game, t_point *point, int color);
void			draw_map(t_game *game);
void			map_mock(t_game *game);

#endif