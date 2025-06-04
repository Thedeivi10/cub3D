/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:40:25 by jotrujil          #+#    #+#             */
/*   Updated: 2025/06/04 14:20:11 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	rotate_player(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_x * cos(angle);
}

void	handle_input(void *param)
{
	t_map	*game;
	double	new_x;
	double	new_y;
	double	speed;

	game = (t_map *)param;
	speed = game->player.move_speed;
	if (game->input.w)
	{
		new_x = game->player.x + game->player.dir_x * speed;
		new_y = game->player.y + game->player.dir_y * speed;
		if (game->grid[(int)new_y][(int)game->player.x] != 1)
			game->player.y = new_y;
		if (game->grid[(int)game->player.y][(int)new_x] != 1)
			game->player.x = new_x;
	}
	if (game->input.right)
		rotate_player(&game->player, -game->player.rot_speed);
	if (game->input.left)
		rotate_player(&game->player, game->player.rot_speed);

	//Call render function again here
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*game;

	game = (t_map *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_W)
		game->input.w = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_S)
		game->input.s = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_A)
		game->input.a = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_D)
		game->input.d = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_LEFT)
		game->input.left = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_RIGHT)
		game->input.right = (keydata.action != MLX_RELEASE);
}
