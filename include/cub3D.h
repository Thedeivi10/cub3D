/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:18:30 by davigome          #+#    #+#             */
/*   Updated: 2025/06/03 14:59:28 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_map
{
	char	**grid;
	int		height;
}				t_map;

typedef struct s_elem
{
	int	n;
	int	s;
	int	e;
	int	w;
	int	c;
	int	f;
}				t_elem;

typedef struct s_start
{
	int	n;
	int	s;
	int	e;
	int	w;
}				t_start;

//UTILS.C
/* When somenthing is wrong, free game and return failure */
void	ft_bad_close(t_map *game);
/* Save memory and copy a matrix */
char	**ft_cpy_matrix(char **src);
/* Check if the value is a space */
int		space(const char *str, int cont);
/* Check if the value is a digit */
int		ft_isdigit(int c);
/* String to int */
int		ft_atoi(const char *str);

//UTILS_2.C
/* Return the size of the map */
int		ft_count_lines(char *map, t_map *game);
/* Free game */
void	ft_free_map(t_map *game);
/* Copy the line read */
void	ft_read_2(int fd, char *line, t_map *game);
/* Read the file */
void	ft_read_map(t_map *game, char **argv);
/* Check .cub */
void	ft_check_name(char **argv);

//ELEMENTS.C
/* Check if the map could not be allocated */
void	ft_init_map(t_map *game);
/* Init the elements to check them */
void	ft_init_elem(t_elem *elem);
/* Check if there are all the elements once */
void	ft_check_elements_2(t_map *game, t_elem *elem);
/* If the elements is rep, his value grow */
void	ft_check_elements_rep(t_map *game, int i, t_elem *elem);

//CHECK_NSWE.C
/* Check if NO has the correct structure */
void	ft_check_n(t_map *game, int i, int j);
/* Check if SO has the correct structure */
void	ft_check_s(t_map *game, int i, int j);
/* Check if WE has the correct structure */
void	ft_check_w(t_map *game, int i, int j);
/* Check if EA has the correct structure */
void	ft_check_e(t_map *game, int i, int j);

//CHECK_AUX_FC.C
/* Check if the value is between 0 and 255 */
int		ft_check_num(t_map *game, int i, int aux, int j);
/* Check if there is anything after the last number */
void	ft_check_next(t_map *game, int i, int j);
/* Check if there is at least a space between F and C with the texture */
void	ft_check_text_space(t_map *game, int i, int j);
/* Check if the first argumen of F and C is a number */
void	ft_check_text_num(t_map *game, int i, int j);
/* Check if there is a comma between the numbers */
void	ft_check_text_comma(t_map *game, int times, int i, int j);

//CHECK_FC.C
/* Check F structure */
void	ft_check_f(t_map *game, int i, int j);
/* Check C structure */
void	ft_check_c(t_map *game, int i, int j);

//CHECKS.C
/* Check if there is only a start point */
void	ft_check_start(t_map *game, int i);
/* Check if the map has the correct structure */
void	ft_flood_fill(char **cpy, int i, int j, t_map *game);
/* When is 0 or a start point, go to floodfill */
void	ft_check_path(t_map *game, int i);
/* Call the functions that check the map */
void	ft_check_map(t_map *game);
/* Call all the check functions */
void	ft_checks(t_map *game, char **argv);

//CHECKS_2.C
/* Call the functions that check elements structures */
void	ft_check_elements_3(t_map *game);
/* Call the functions that check the elements */
void	ft_check_elements(t_map *game);
/* Search if the is any invalid char in the map */
void	ft_invalid_char(t_map *game, int i);
/* Init the start points count */
void	ft_init_start(t_start *start);
/* When found a start point the value grow */
void	ft_check_start_2(t_map *game, int i, int j, t_start *start);

//CHECKS_3.C
/* Aux of floodfill */
void	ft_aux_flood(char **cpy, int i, int j, t_map *game);

#endif
