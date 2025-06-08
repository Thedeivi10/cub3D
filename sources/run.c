/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:36:24 by davigome          #+#    #+#             */
/*   Updated: 2025/06/08 11:44:35 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

void	ft_init_mlx(t_map	*game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!game->mlx)
	{
		fprintf(stderr, "Error:\nCould not init MLX42");
		ft_bad_close(game);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		fprintf(stderr, "Error:\nCould not create image");
		ft_bad_close(game);
	}
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void init_player_position(t_map *game)
{
    int x;
    int y;
    
    y = 0;
    // Saltamos las líneas de configuración (texturas, colores)
    while (game->grid[y] && (game->grid[y][0] == 'N' || game->grid[y][0] == 'S' || 
           game->grid[y][0] == 'E' || game->grid[y][0] == 'W' ||
           game->grid[y][0] == 'F' || game->grid[y][0] == 'C' ||
           game->grid[y][0] == '\n'))
        y++;
    
    // Ahora buscamos en el mapa real
    while (game->grid[y])
    {
        x = 0;
        while (game->grid[y][x])
        {
            if (game->grid[y][x] == 'N' || game->grid[y][x] == 'S' || 
                game->grid[y][x] == 'E' || game->grid[y][x] == 'W')
            {
                // Posición del jugador (centrado en la casilla)
                game->player.x = (double)x + 0.5;
                game->player.y = (double)y + 0.5;
                
                // Dirección y plano según la orientación
                if (game->grid[y][x] == 'N')
                {
                    game->player.dir_x = 0;
                    game->player.dir_y = -1;
                    game->player.plane_x = 0.66;
                    game->player.plane_y = 0;
                }
                else if (game->grid[y][x] == 'S')
                {
                    game->player.dir_x = 0;
                    game->player.dir_y = 1;
                    game->player.plane_x = -0.66;
                    game->player.plane_y = 0;
                }
                else if (game->grid[y][x] == 'E')
                {
                    game->player.dir_x = 1;
                    game->player.dir_y = 0;
                    game->player.plane_x = 0;
                    game->player.plane_y = 0.66;
                }
                else if (game->grid[y][x] == 'W')
                {
                    game->player.dir_x = -1;
                    game->player.dir_y = 0;
                    game->player.plane_x = 0;
                    game->player.plane_y = -0.66;
                }
                
                // Velocidades
                game->player.move_speed = 0.05;
                game->player.rot_speed = 0.03;
                
                // Reemplaza el carácter en el mapa
                // game->grid[y][x] = '0'; // Descomentar si quieres quitar el jugador del mapa
                
                return;
            }
            x++;
        }
        y++;
    }
    
    fprintf(stderr, "Error: No se encontró posición inicial del jugador\n");
    ft_bad_close(game);
}

void	ft_run(t_map *game)
{
	ft_init_mlx(game);
	ft_load_textures(game);
	init_player_position(game);
	mlx_loop_hook(game->mlx, &update_game, game);
	mlx_key_hook(game->mlx, &key_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
