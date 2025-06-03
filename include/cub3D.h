/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:18:30 by davigome          #+#    #+#             */
/*   Updated: 2025/06/03 14:04:36 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <sys/time.h>

// MLX GAME MACROS

# define SIZE_W 1920
# define SIZE_H 1080

typedef struct s_map
{
	char	**grid;
	int		height;
}			t_map;

typedef struct s_elem
{
	int	n;
	int	s;
	int	e;
	int	w;
	int	c;
	int	f;
}		t_elem;

typedef struct s_start
{
	int	n;
	int	s;
	int	e;
	int	w;
}				t_start;

typedef struct s_player
{
	int		player_x;
	int		player_y;
	double	p_angle;
	int		p_rotation;
	float	fov_radians;
}			t_player;

typedef struct s_textures
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
}			t_textures;

typedef struct s_mlx
{
	mlx_t		*mlx_pointer;
	t_player	*player;
	t_textures	*tex;
}				t_mlx;

//UTILS.C
void	ft_bad_close(t_map *game);
char	**ft_cpy_matrix(char **src);
int		space(const char *str, int cont);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

//UTILS_2.C
int		ft_count_lines(char *map, t_map *game);
void	ft_free_map(t_map *game);
void	ft_read_2(int fd, char *line, t_map *game);
void	ft_read_map(t_map *game, char **argv);
void	ft_check_name(char **argv);

//ELEMENTS.C
void	ft_init_map(t_map *game);
void	ft_init_elem(t_elem *elem);
void	ft_check_elements_2(t_map *game, t_elem *elem);
void	ft_check_elements_rep(t_map *game, int i, t_elem *elem);

//CHECK_NSWE.C
void	ft_check_n(t_map *game, int i, int j);
void	ft_check_s(t_map *game, int i, int j);
void	ft_check_w(t_map *game, int i, int j);
void	ft_check_e(t_map *game, int i, int j);

//CHECK_AUX_FC.C
int		ft_check_num(t_map *game, int i, int aux, int j);
void	ft_check_next(t_map *game, int i, int j);
void	ft_check_text_space(t_map *game, int i, int j);
void	ft_check_text_num(t_map *game, int i, int j);
void	ft_check_text_comma(t_map *game, int times, int i, int j);

//CHECK_FC.C
void	ft_check_f(t_map *game, int i, int j);
void	ft_check_c(t_map *game, int i, int j);

//CHECKS.C
void	ft_check_start(t_map *game, int i);
void	ft_flood_fill(char **cpy, int i, int j, t_map *game);
void	ft_check_path(t_map *game, int i);
void	ft_check_map(t_map *game);
void	ft_checks(t_map *game, char **argv);

//CHECKS_2.C
void	ft_check_elements_3(t_map *game);
void	ft_check_elements(t_map *game);
void	ft_invalid_char(t_map *game, int i);
void	ft_init_start(t_start *start);
void	ft_check_start_2(t_map *game, int i, int j, t_start *start);

//CHECKS_3.C
void	ft_aux_flood(char **cpy, int i, int j, t_map *game);

#endif
