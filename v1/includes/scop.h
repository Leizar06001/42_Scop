#ifndef SCOP_H
#define SCOP_H

#include <stdbool.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define ON_DESTROY		17
#define ON_KEYDOWN		2
#define ON_KEYUP		3

#define KEY_A		    100
#define KEY_D		    97
#define KEY_S		    115
#define KEY_W			119
#define KEY_ESCAPE		65307
#define KEY_ARR_UP		65362
#define KEY_ARR_DOWN	65364
#define KEY_ARR_LEFT	65361
#define KEY_ARR_RIGHT	65363

// typedef struct s_imgd
// {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
//     bool    img_exists;
// }				t_imgd;

// typedef struct s_data {
//     void    *mlx;
//     void    *win;
//     t_imgd	img;
//     char    *addr;
//     int     bits_per_pixel;
//     int     line_length;
//     int     endian;
// }               t_data;

// typedef struct	s_env
// {
// 	t_win		win;
// 	t_sim		sim;
// 	t_cam		cam;
// 	t_key		key[MAX_KEYS];
// 	t_mod		mod;
// 	t_buffer	buffer;
// 	t_shader	shader;
// 	t_model		model;
// }				t_env;


// void	ft_put_pixel(t_imgd *img, int x, int y, int color);
// void	draw_line(t_imgd *img, float startx, float starty, float endx, float endy, int line_width, int color);


#endif
