/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:41:15 by shima             #+#    #+#             */
/*   Updated: 2022/11/10 12:48:37 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_game_info(t_game_info *info);
int		main_loop(t_game_info *info);
int		key_hook(int keycode, t_game_info *info);

void	load_texture(t_game_info *info);
void	load_image(void *mlx_ptr, int *texture, char *path);

int worldMap[mapWidth][mapHeight]=
{
  {8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
  {8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
  {7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
  {7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
  {2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
  {2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
  {2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
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
	info->posX = 22.0;
	info->posY = 11.5;
	info->dirX = -1.0;
	info->dirY = 0.0;
	info->planeX = 0.0;
	info->planeY = 0.66;
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;

	load_texture(info);
	info->img.img = mlx_new_image(info->mlx_ptr, screenWidth, screenHeight);
	info->img.addr = (int *)mlx_get_data_addr(info->img.img, &info->img.bits_per_pixel, &info->img.size_line, &info->img.endian);
}

void	load_texture(t_game_info *info)
{
	load_image(info->mlx_ptr, info->texture[0], "textures/eagle.xpm");
	load_image(info->mlx_ptr, info->texture[1], "textures/wood.xpm");
	load_image(info->mlx_ptr, info->texture[2], "textures/purplestone.xpm");
	load_image(info->mlx_ptr, info->texture[3], "textures/greystone.xpm");
	load_image(info->mlx_ptr, info->texture[4], "textures/bluestone.xpm");
	load_image(info->mlx_ptr, info->texture[5], "textures/mossy.xpm");
	load_image(info->mlx_ptr, info->texture[6], "textures/redbrick.xpm");
	load_image(info->mlx_ptr, info->texture[7], "textures/colorstone.xpm");
}

void	load_image(void *mlx_ptr, int *texture, char *path)
{
	t_img	img;
	int x;
	int y;

	img.img = mlx_xpm_file_to_image(mlx_ptr, path, &img.width, &img.height);
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);
	y = 0;
	while (y < img.height)
	{
		x = 0;
		while (x < img.width)
		{
			texture[img.width * y + x] = img.addr[img.width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(mlx_ptr, img.img);
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
	int y;
	// FLOOR CASTING
	y = 0;
	while (y < screenHeight)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = info->dirX - info->planeX;
		float rayDirY0 = info->dirY - info->planeY;
		float rayDirX1 = info->dirX + info->planeX;
		float rayDirY1 = info->dirY + info->planeY;
		
		// Current y position compared to the center of the screen (the horizon)
		// y=0, -240
		// y=1, -239
		// y=240, 0
		// y=479, 239
		int p = y - screenHeight / 2;

		// Vertical position of the camera.
		// 240
		float posZ = 0.5 * screenHeight;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and celling
		// -1 <= rowDistance <= 1
		float rowDistance = posZ / p;

		// calclate the real world step vecter we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;

		// real world coordinates of the leftmost column. this will be updated as we step to the right
		float floorX = info->posX + rowDistance * rayDirX0;
		float floorY = info->posY + rowDistance * rayDirY0;

		x = 0;
		while (x < screenWidth)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			int floorTexture = 3;
			int ceilingTexture = 6;
			int color;

			// floor
			color = (info->texture)[floorTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			(info->buffer)[y][x] = color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = (info->texture)[ceilingTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			(info->buffer)[screenHeight - y - 1][x] = color;

			x++;
		}
		y++;
	}

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
