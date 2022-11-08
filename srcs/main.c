/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:41:15 by shima             #+#    #+#             */
/*   Updated: 2022/11/08 16:37:21 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_game_info(t_game_info *info);
int		main_loop(t_game_info *info);
int		key_hook(int keycode, t_game_info *info);

int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7}, 
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7}, 
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7}, 
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7}, 
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7}, 
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7}, 
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1}, 
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3} 
};


int main(int argc, char *argv[])
{
	t_game_info	info;
	
	info.mlx_ptr = mlx_init();
	info.win_ptr = mlx_new_window(info.mlx_ptr, screenWidth, screenHeight, "cub3D");
	init_game_info(&info);
	mlx_loop_hook(info.mlx_ptr, &main_loop, &info);
	mlx_key_hook(info.win_ptr, &key_hook, &info);
	mlx_loop(info.mlx_ptr);
}

void	init_game_info(t_game_info *info)
{
	int x;
	int y;
	info->posX = 22.0;
	info->posY = 11.5;
	info->dirX = -1.0;
	info->dirY = 0.0;
	info->planeX = 0.0;
	info->planeY = 0.66;
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;
	x = 0;
	// generate some textures;
	while (x < texWidth)
	{
		y = 0;
		while (y < texHeight)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			// flat red texture with black cross
			(info->texture)[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y);
			// sloped greyscale
			(info->texture)[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			// sloped yellow gradient
			(info->texture)[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor;
			// xor grayscale
			(info->texture)[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			// xor green
			(info->texture)[4][texWidth * y + x] = 256 * xorcolor;
			// red bricks
			(info->texture)[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16);
			// red gradient
			(info->texture)[6][texWidth * y + x] = 65536 * ycolor;
			// flat grey texture
			(info->texture)[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128;
			y++;
		}
		x++;
	}
	info->img.img = mlx_new_image(info->mlx_ptr, screenWidth, screenHeight);
	info->img.addr = (int *)mlx_get_data_addr(info->img.img, &info->img.bits_per_pixel, &info->img.size_line, &info->img.endian);
}

void	draw(t_game_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < screenHeight)
	{
		x = 0;
		while (x < screenWidth)
		{
			info->img.addr[y * screenWidth + x] = info->buffer[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img.img, 0, 0);
}

void	calc(t_game_info *info)
{
	int	x;
	x = 0;
	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			info->buffer[i][j] = 0;
		}
	}
	while (x < screenWidth)
	{
		// x=0,-1
		// x=1,-319/320
		// x=2,-318/320
		// x=3,-317/320
		// ...
		// x=319,-1/320  
		// x=320,0
		// x=321,1/320
		// ...
		// x=637,317/320
		// x=638,318/320
		// x=639,319/320
		// 6cmの1/3は 6 * 1/3 = 2のようにcameraXは割合
		double cameraX = 2 * x / (double)screenWidth - 1;

		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX;

		//which box of the map we're in
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// length of ray from one x or y-side to next x or y-side
		// deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
		// deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		// ↑三角比の計算
		// 斜辺 = √a^2 + b^2
		// 高さは底辺 * tanθ (1 * dirY/dirX)
		// tanθ = 高さ/底辺 (dirY/dirX)
		// deltaDistX,Yは式変形で次のように表せられる。
		// |sqrt(X^2 + Y^2) / X|
		// |sqrt(X^2 + Y^2) / Y|
		// DDAでは比率が欲しいので sqrt(X^2 + Y^2)を1にしてしまう
		// |1 / X|
		// |1 / Y|
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
	
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		// deltaDistXの増加分を掛けてる？
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		// Calculate distance projected on camera direction (Euclidean distance would give fisheye effect)
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		// Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		// Calculate lowest and highest pixel to fill in current stripe
		// -lineHeight / 2 + screenHeight / 2
		// なぜ上の式になるかは実際にやってみるとわかりやすい。結論はこの式が一番見やすいからということになる。
		// lineHeight だけ -> lineH + screenH -> lineH + screenH / 2 -> lineH /2 + screenH / 2
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		// texturing calculations
		// 1 substracted fron it so that texture 0 can be used!
		int	texNum = worldMap[mapX][mapY] - 1;

		// calculate value of wallX
		// where exactly the wall was hit
		double wallX;
		if (side == 0)
			wallX = info->posY + perpWallDist * rayDirY;
		else
			wallX = info->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		// 1.0は小数で計算するためにしている。
		double step = 1.0 * texHeight / lineHeight;
		// double step = 1.0 * lineHeight / texHeight;
		// Starting texture coordinate
		// -lineHeight / 2 + screenHeight / 2 >= 0
		// そのままtexPos 0で描画されればいい
		// -lineHeight / 2 + screenHeight / 2 < 0
		// その分を増やして、stepで減らす。
		double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
		// printf("drawstart: %d\n", drawStart);
		// printf("texPos: %f\n", texPos);
		int y;
		y = drawStart;
		while (y < drawEnd)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight -1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = (info->texture)[texNum][texHeight * texY + texX];
			// make color darker for y-sides: R, G, B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			info->buffer[y][x] = color;
			y++;
		}
		x++;
	}
}

int	main_loop(t_game_info *info)
{
	calc(info);
	draw(info);
	return (EXIT_SUCCESS);
}

int	key_hook(int keycode, t_game_info *info)
{
	if (keycode == KEY_W)
	{
		if (worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)info->posY] == false)
			info->posX += info->dirX * info->moveSpeed;
		if (worldMap[(int)info->posX][(int)(info->posY + info->dirY * info->moveSpeed)] == false)
			info->posY += info->dirY * info->moveSpeed;
	}
	else if (keycode == KEY_S)
	{
		if (worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)info->posY] == false)
			info->posX -= info->dirX * info->moveSpeed;
		if (worldMap[(int)info->posX][(int)(info->posY - info->dirY * info->moveSpeed)] == false)
			info->posY -= info->dirY * info->moveSpeed;
	}
	else if (keycode == KEY_D)
	{
		// both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-(info->rotSpeed)) - info->dirY * sin(-(info->rotSpeed));
		info->dirY = oldDirX * sin(-(info->rotSpeed)) + info->dirY * cos(-(info->rotSpeed));
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-(info->rotSpeed)) - info->planeY * sin(-(info->rotSpeed));
		info->planeY = oldPlaneX * sin(-(info->rotSpeed)) + info->planeY * cos(-(info->rotSpeed));
	}
	else if (keycode == KEY_A)
	{
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	else if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
