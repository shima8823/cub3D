/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:41:15 by shima             #+#    #+#             */
/*   Updated: 2022/11/08 18:59:33 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		raycast_loop(t_game_info *info);
void	init_game_info(t_game_info *info);
int		verLine(t_game_info *info, int x, int drawStart, int drawEnd, int color);
int		key_hook(int keycode, t_game_info *info);

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


int main(int argc, char *argv[])
{
	t_game_info	info;
	
	info.mlx_ptr = mlx_init();
	info.win_ptr = mlx_new_window(info.mlx_ptr, screenWidth, screenHeight, "cub3D");
	init_game_info(&info);
	mlx_loop_hook(info.mlx_ptr, &raycast_loop, &info);
	mlx_key_hook(info.win_ptr, &key_hook, &info);
	mlx_loop(info.mlx_ptr);

}

void	init_game_info(t_game_info *info)
{
	info->posX = 12;
	info->posY = 5;
	info->dirX = -1;
	info->dirY = 0;
	info->planeX = 0;
	info->planeY = 0.66;
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;
}

int	raycast_loop(t_game_info *info)
{
	int	x;
	x = 0;
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
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
			// perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;
			// perpWallDist = (sideDistY - deltaDistY);

		// Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		// Calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		// choose wall color
		int color;
		if (worldMap[mapX][mapY] == 1)
			color = 0xFF0000;
		else if (worldMap[mapX][mapY] == 2)
			color = 0x00FF00;
		else if (worldMap[mapX][mapY] == 3)
			color = 0x0000FF;
		else if (worldMap[mapX][mapY] == 4)
			color = 0xFFFFFF;
		else 
			color = 0xFFFF00;

		// give x and y sides different brightness
		if (side == 1)
			color = color / 2;
		verLine(info, x, drawStart, drawEnd, color);
		x++;
	}
	return (EXIT_SUCCESS);
}

int	verLine(t_game_info *info, int x, int drawStart, int drawEnd, int color)
{
	int y;

	y = drawStart;
	while (y <= drawEnd)
	{
		mlx_pixel_put(info->mlx_ptr, info->win_ptr, x, y, color);
		y++;
	}
	return (0);
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
