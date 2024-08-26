#include "scop.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_put_pixel(t_imgd *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_imgd *img, float startx, float starty, float endx, float endy, int line_width, int color)
{
	int		steps;
	float	xinc, yinc;
	float	x, y;
	int		i, j;

	if (abs((int)round(endx - startx))
		> abs((int)round(endy - starty)))
		steps = abs((int)round(endx - startx));
	else
		steps = abs((int)round(endy - starty));
	xinc = (float)(endx - startx) / steps;
	yinc = (float)(endy - starty) / steps;
	j = -1;
	while (++j < line_width)
	{
		x = startx;
		y = starty;
		i = -1;
		while (++i <= steps)
		{
			ft_put_pixel(img, (int)round(x - line_width
					+ j), (int)round(y), color);
			x += xinc;
			y += yinc;
		}
	}
}