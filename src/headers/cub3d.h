/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:12:04 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/20 10:15:12 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <time.h>
# include <mlx.h>
# include <mlx_int.h>
# include "keys.h"
# include "libft.h"

# define screenWidth 1920
# define screenHeight 1080

typedef struct s_map
{
	char **worldMap;
	int width;
	int height;
}	t_map;

typedef struct s_data
{
    void            *img;
    char            *addr;
    int             bits_per_pixel;
    int             line_length;
    int             endian;
}		t_data;

typedef struct s_player
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    double moveSpeed;
    double rotSpeed;
}	t_player;

typedef struct s_vars
{
    void            *mlx;
    void            *win;
    t_data          img;
    int             x;
    int             y;
    t_player        player;
    t_map           map;
    char            *no_texture;
    char            *so_texture;
    char            *we_texture;
    char            *ea_texture;
    int             floor_color[3];
    int		ceiling_color[3];
    int		floor_color_hex;
    int		ceiling_color_hex;
}		t_vars;

typedef struct s_draw_params
{
    int	x;
    int	drawStart;
    int	drawEnd;
    int	color;
    double	perpwalldist;
    t_vars *vars;
}	t_draw_params;

int init_game_struct(t_vars *vars);
int	parse_config(char *path, t_vars *vars);
void	print_texture_paths(t_vars *vars);
void	print_colors(t_vars *vars);
//void	print_map(t_vars *vars);
int		keypress(int keycode, t_vars *vars);
int		keyrelease(int keycode, t_vars *vars);
int		destroy(int keycode, t_vars *vars);
int		motion(int button, int x, int y, t_vars *vars);
char	*ft_strdup(const char *s1);
char	*ft_itoa(int n);
void	update_player_position(t_vars *vars, int key_pressed);
void	move_player(t_vars *vars, double moveSpeed);
void	rotate_player(t_vars *vars, double rotSpeed);
void	display_debug_info(t_vars *vars, int key_pressed);
void	draw_line(t_draw_params params);
void	draw_frame(t_vars *vars);
void	calculateRay(int x, t_vars *vars, double *perpWallDist, int *color);
t_vars	*root_init(t_vars *vars);
void	calculate_fps(t_vars *vars);
void free_vars(t_vars *vars);
void ft_free(void *ptr);

//map
//   map.c
bool is_map_valid(t_vars *vars);
bool have_onlyvalid_ch(t_vars *vars);
bool is_player_valid(t_vars *vars);
bool is_map_closed(char **map);
bool is_last_column_closed(char **map);

//   map1.c
bool    are_all_lines_valid(t_vars *vars);
bool    is_line_horizontal_valid(char *line);
bool    is_line_vertical_valid(char **map);
int     is_line_vertical_valid_aux(int *l, int *ch, int *qt_l, int *qt_ch);
bool    is_first_last_valid(char **map);

bool is_empty_line(char *line);

//utils
//   utils_maps.c
bool	jump_spaces(char ch, int *j, int backwards);
#endif
