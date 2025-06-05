/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:15:04 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/22 04:00:41 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define MINIMAP_SCALE 0.35
# define FOV 1.0
# define PLAYER_SPEED 0.03
# define COLLISION_DISTANCE 0.2

typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct s_view
{
	t_point		position;
	t_point		direction;
}				t_view;

typedef struct s_ray
{
	t_point		start;
	t_point		direction;
	t_point		scale;
}				t_ray;

typedef struct s_scene
{
	char		*north_tex;
	char		*south_tex;
	char		*east_tex;
	char		*west_tex;
	int			floor_color;
	int			ceiling_color;
}				t_scene;

typedef struct s_game
{
	t_view		player;
	int			width;
	int			height;
	char		**s_map;
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*buffer;
}				t_game;

/**
 * collision.c
 */
void			check_collisions(t_game *game, t_point *collisions);

/**
 * hooks.c
 */
void			draw_hook(void *param);
void			key_hook(void *param);

/**
 * minimap.c
 */
void			draw_minimap(t_game *game);
void			draw_point(t_game *game, t_point *point, int color);

/**
 * mlx.c
 */
void			mlx(t_game *game);

/**
 * movement.c
 */
void			rotate_view(t_view *view, double angle);
void			move_view(t_game *game, t_view *view, t_point *direction);

/**
 * ray.c
 */
void			init_ray(t_ray *ray, t_view *view);
void			collide_ray(t_game *game, t_ray *ray, t_point *collision,
					t_point *direction);

/**
 * scene.c
 */
void			draw_scene(t_game *game);

/**
 * vector.c
 */
void			norm(t_point *vector);
double			v_length(t_point *vector);

/**
 * FOR DEBUG PURPOSES
 * map_mock.c
 */
void			map_mock(t_game *game);

#endif